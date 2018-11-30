#include "gameexecuter.hh"
#include "actor.hh"
#include "gameexception.hh"
#include "illegalmoveexception.hh"
#include <QDebug>
#include <algorithm>
#include <iostream>
#include <vector>

namespace Student {

GameExecuter::GameExecuter(
    std::shared_ptr<Common::IGameRunner> gameRunner,
    std::shared_ptr<GameBoard> gameBoard, std::shared_ptr<GameState> gameState,
    SpinnerContainerWidget *spinnerWidget, GameBoardWidget *gameBoardWidget,
    std::vector<std::shared_ptr<Student::Player>> playerVector,
    Student::UserGuideWidget *userGuide, PlayerPointsWidget *playerPointsWidget)
    : QObject(), gameRunner_(gameRunner), gameBoard_(gameBoard),
      gameState_(gameState), spinnerWidget_(spinnerWidget),
      gameBoardWidget_(gameBoardWidget), playerVector_(playerVector),
      userGuide_(userGuide), playerPointsWidget_(playerPointsWidget),
      selectedHexCoordinates_(Common::CubeCoordinate()), isHexSelected_(false),
      isWheelSpun_(false), selectedActorId_(-1),
      movesOfSpunActor_(std::string()) {

  connect(gameBoardWidget_, &GameBoardWidget::hexClicked, this,
          &GameExecuter::handleHexClick);
  connect(spinnerWidget_, &SpinnerContainerWidget::spinningFinished, this,
          &GameExecuter::handleSpin);

  gameState->changePlayerTurn(1);
  gameState->changeGamePhase(Common::GamePhase::MOVEMENT);
  userGuide_->setPlayerInTurn(getCurrentPlayer());
  userGuide->setNextActionGuide(
      "Aloita klikkaamalla ruutua josta haluat siirtää nappulan");
  userGuide_->setAdditionalMessage(
      "Tervetuloa pelaamaan LoveIsland Suomi 2018-peliä!");
}

void GameExecuter::skipCurrentPhaseRequested() {
  goToNextState();
  userGuide_->setAdditionalMessage("Skippasit vuoron");
}

void GameExecuter::handleHexClick(Common::CubeCoordinate coordinates) {
  switch (gameRunner_->currentGamePhase()) {
  case Common::GamePhase::MOVEMENT:
    handlePhaseMovement(coordinates);
    break;
  case Common::GamePhase::SINKING:
    handlePhaseSinking(coordinates);
    break;
  case Common::GamePhase::SPINNING:
    handlePhaseSpinning(coordinates);
    break;
  default:
    return;
  }
  gameBoardWidget_->updateBoard();
}

void GameExecuter::handlePhaseMovement(Common::CubeCoordinate coord) {
  std::shared_ptr<Common::Hex> clickedHex = gameBoard_->getHex(coord);

  if (clickedHex == nullptr) {
    userGuide_->setAdditionalMessage(
        "Virhe pelissä! "
        "Klikkaamaasi ruutua ei ole olemassa, älä ota yhteyttä kehittäjiin "
        "vaan pure hammasta!"
        " tai käynnistä peli uudelleen");
  } else if (!isHexSelected_) {
    if (isPlayerPawnsInHex(coord)) {
      selectedHexCoordinates_ = coord;
      isHexSelected_ = true;
      userGuide_->setAdditionalMessage("Ruutu valittu!");
      userGuide_->setNextActionGuide(
          "Valitse ruutu johon haluat liikuttaa nappulan.");
    } else {
      userGuide_->setAdditionalMessage(
          "Et voi valita ruutua, jossa sinulla ei ole yhtään nappia.");
    }
  } else {
    if (selectedHexCoordinates_.operator==(coord)) {
      isHexSelected_ = false;
      userGuide_->setAdditionalMessage(
          "Valinta poistettu klikkaamastasi ruudusta.");
      userGuide_->setNextActionGuide(
          "Valitse ruutu josta haluat liikuttaa nappulan.");
    } else {
      if (!tryMoveTransport(coord)) {
        // jos transportin liikuttaminen ei ole mahdollista liikutetaan pawnia
        tryMovePawn(coord);
      }
      doActionsOfAllActors();
    }
  }
  if (getCurrentPlayer()->getActionsLeft() == 0) {
    goToNextState();
  }
}

void GameExecuter::handlePhaseSinking(Common::CubeCoordinate coord) {
  if (tryFlipTile(coord)) {
    goToNextState();
  }
}

void GameExecuter::handlePhaseSpinning(Common::CubeCoordinate coord) {
  if (!isWheelSpun_) {
    userGuide_->setAdditionalMessage(
        "Kiekko ei ollut vielä pyörähtänyt, odota että se pyörähtää loppuun.");
    return;
  }
  if (!isHexSelected_) {
    if (trySelectActor(typeOfSpunActor_, coord)) {
      selectedHexCoordinates_ = coord;
      userGuide_->setAdditionalMessage("Toimija valittu.");
      userGuide_->setNextActionGuide(
          "Klikkaa ruutua, johon haluat siirtää toimijan.");
      isHexSelected_ = true;
      return;
    } else if (trySelectTransport(typeOfSpunActor_, coord)) {
      selectedHexCoordinates_ = coord;
      userGuide_->setAdditionalMessage("Kuljettaja valittu.");
      userGuide_->setNextActionGuide(
          "Klikkaa ruutua, johon haluat siirtää kuljettajan.");
      isHexSelected_ = true;
      return;
    }
    userGuide_->setAdditionalMessage(
        "Et voi valita toimijaa/kuljettajaa kyseisessä ruudussa");
    userGuide_->setNextActionGuide(
        "Yritä valita toimija/kuljettaja toisesta ruudusta");
    return;
  }

  if (selectedHexCoordinates_.operator==(coord)) {
    isHexSelected_ = false;
    userGuide_->setAdditionalMessage("Ei ruutua valittuna.");
    userGuide_->setNextActionGuide(
        "Valitse ruutu josta liikutat toimijaa/kuljettajaa");
    return;
  }

  if (tryMoveActor(coord)) {
    tryDoActor(typeOfSpunActor_, coord);
    goToNextState();
    userGuide_->setAdditionalMessage(
        "Liikutit toimijan ja se toteutti toimintonsa!");
    return;
  }

  if (tryMoveTransportWithSpinner(coord, movesOfSpunActor_)) {
    goToNextState();
    userGuide_->setAdditionalMessage(
        "Liikutit kuljettajan ja siinä olevat napit!");
    return;
  } else {
    userGuide_->setAdditionalMessage(
        "Et voi liikuttaa toimijaa/kuljettajaa klikkaamaasi ruutuun");
  }
}

void GameExecuter::handleSpin() {
  isWheelSpun_ = true;
  if (!gameBoard_->isAnyActorsOrTransportsOfType(typeOfSpunActor_)) {
    gamePhaseToMovement();
    userGuide_->setAdditionalMessage(
        "Laudalla ei ole käännettynä yhtään kiekon arpomaa toimijaa. Vuoro "
        "siirtyi seuraavalle pelaajalle.");
    return;
  }
  userGuide_->setNextActionGuide("Valitse toimija, jota haluat liikuttaa.");
  userGuide_->setAdditionalMessage("Kiekko pyörähti, näet siitä minkä "
                                   "tyyppistä toimijaa sinun tulee liikuttaa.");
}

bool GameExecuter::trySelectActor(std::string type,
                                  Common::CubeCoordinate coord) {
  for (auto const &a : gameBoard_->getHex(coord)->getActors()) {
    if (a->getActorType() == type) {
      selectedActorId_ = a->getId();
      return true;
      ;
    }
  }
  selectedActorId_ = -1;
  return false;
}

bool GameExecuter::trySelectTransport(std::string type,
                                      Common::CubeCoordinate coord) {
  for (auto const &t : gameBoard_->getHex(coord)->getTransports()) {
    if (t->getTransportType() == type) {
      selectedActorId_ = t->getId();
      return true;
    }
  }
  selectedActorId_ = -1;
  return false;
}

bool GameExecuter::tryMoveActor(Common::CubeCoordinate to) {
  if (gameRunner_->checkActorMovement(selectedHexCoordinates_, to,
                                      selectedActorId_, movesOfSpunActor_)) {
    gameRunner_->moveActor(selectedHexCoordinates_, to, selectedActorId_,
                           movesOfSpunActor_);
    return true;
  }
  return false;
}

bool GameExecuter::tryMoveTransport(Common::CubeCoordinate to) {
  try {
    for (auto const &transport :
         gameBoard_->getHex(selectedHexCoordinates_)->getTransports()) {
      putPawnsToTransport(transport->getTransportType(),
                          selectedHexCoordinates_);
      int movesLeft = gameRunner_->moveTransport(selectedHexCoordinates_, to,
                                                 transport->getId());
      if (movesLeft >= 0) {
        userGuide_->setAdditionalMessage(
            "Kuljettaja ja siinä olevat nappulat liikutettu");
        userGuide_->setNextActionGuide(
            "Valitse ruutu josta haluat liikuttaa nappuloita");
        isHexSelected_ = false;
        return true;
      }
    }
    userGuide_->setAdditionalMessage(
        "Et voi siirtää kuljettajaa klikkaamaasi ruutuun");
    return false;
  } catch (Common::IllegalMoveException &e) {
    userGuide_->setAdditionalMessage(
        "Et voi siirtää kuljettajaa klikkaamaasi ruutuun");
    return false;
  }
}

bool GameExecuter::tryMovePawn(Common::CubeCoordinate to) {
  std::vector<std::shared_ptr<Common::Pawn>> playerPawnsInSelected =
      getPlayerPawnsInCoordinate(selectedHexCoordinates_);
  isHexSelected_ = false;
  if (playerPawnsInSelected.size() != 0) {
    try {
      getCurrentPlayer()->setActionsLeft(gameRunner_->movePawn(
          selectedHexCoordinates_, to, playerPawnsInSelected.front()->getId()));
      userGuide_->setAdditionalMessage("Nappula liikutettu onnistuneesti.");
      userGuide_->setNextActionGuide(
          "Valitse ruutu josta haluat liikuttaa nappulan.");
      return true;
    } catch (Common::IllegalMoveException) {
      userGuide_->setAdditionalMessage(
          "Et voi liikuttaa nappulaa klikkaamaasi ruutuun!");
      userGuide_->setNextActionGuide(
          "Valitse uudelleen ruutu josta haluat liikuttaa nappulan.");
    }
  } else {
    userGuide_->setAdditionalMessage(
        "Valitsemassasi ruudussa ei ole yhtään nappulaa joita voisit "
        "liikuttaa, valinta poistettu");
  }
  return false;
}

bool GameExecuter::tryMoveTransportWithSpinner(Common::CubeCoordinate to,
                                               std::string moves) {
  putPawnsToTransport(typeOfSpunActor_, selectedHexCoordinates_);
  try {
    gameRunner_->moveTransportWithSpinner(selectedHexCoordinates_, to,
                                          selectedActorId_, moves);
    return true;
  } catch (Common::IllegalMoveException &e) {
    return false;
  }
}

bool GameExecuter::tryFlipTile(Common::CubeCoordinate coord) {
  std::shared_ptr<Common::Hex> clickedHex = gameBoard_->getHex(coord);
  try {
    std::string actor = gameRunner_->flipTile(coord);
    // if was actor in clicked hex and it can do
    if (tryDoActor(actor, coord)) {
      userGuide_->setAdditionalMessage(
          "Ruutu upotettu, toimija teki toimintonsa!");
      return true;
    }
    // if was transport in clicked hex
    if (putPawnsToTransport(actor, coord)) {
      userGuide_->setAdditionalMessage("Ruutu upotettu!");
      return true;
    }
  } catch (Common::IllegalMoveException &e) {
    userGuide_->setAdditionalMessage("Et voi kääntää klikkaamaasi ruutua.");
    return false;
  }
  return false;
}

bool GameExecuter::tryDoActor(std::string type, Common::CubeCoordinate coord) {
  std::shared_ptr<Common::Hex> hexInCoord = gameBoard_->getHex(coord);
  // etsitään oikeaa tyyppiä oleva aktori
  for (auto const &actor : hexInCoord->getActors()) {
    if (actor->getActorType() == type) {
      actor->doAction();
      return true;
    }
  }
  return false;
}

void GameExecuter::gamePhaseToMovement() {
  isWheelSpun_ = false;
  isHexSelected_ = false;
  gameState_->changeGamePhase(Common::GamePhase::MOVEMENT);
  userGuide_->setNextActionGuide(
      "Valitse liikutettava nappula klikkaamalla ruutua");
  updatePoints();
  moveToNextPlayerTurn();
}

void GameExecuter::gamePhaseToSinking() {
  gameState_->changeGamePhase(Common::GamePhase::SINKING);
  userGuide_->setNextActionGuide("Valitse upotettava ruutu.");
  userGuide_->setAdditionalMessage(
      "Liikkusi loppuivat, pelivaihe on nyt upotus.");
}

void GameExecuter::gamePhaseToSpinning() {
  isWheelSpun_ = false;
  isHexSelected_ = false;
  gameState_->changeGamePhase(Common::GamePhase::SPINNING);
  std::pair<std::string, std::string> spinResult = gameRunner_->spinWheel();
  typeOfSpunActor_ = spinResult.first;
  movesOfSpunActor_ = spinResult.second;
  spinnerWidget_->beginSpin(spinResult.first, spinResult.second);
  userGuide_->setNextActionGuide("Odota, että kiekko pyörähtää.");
}

bool GameExecuter::putPawnsToTransport(std::string type,
                                       Common::CubeCoordinate coord) {
  std::shared_ptr<Common::Hex> hexInCoord = gameBoard_->getHex(coord);
  // etsitään oikeaa tyyppiä oleva transport ruudusta
  for (auto const &t : hexInCoord->getTransports()) {
    if (t->getTransportType() == type) {
      // yritetään lisätä transporttiin kaikki ruudun pawnit jotka eivät jo ole
      // transportissa
      for (auto const &pawn : hexInCoord->getPawns()) {
        if (!t->isPawnInTransport(pawn)) {
          t->addPawn(pawn);
        }
      }
      return true;
    }
  }
  return false;
}

std::vector<std::shared_ptr<Common::Pawn>>
GameExecuter::getPlayerPawnsInCoordinate(Common::CubeCoordinate coord) {
  std::vector<std::shared_ptr<Common::Pawn>> pawnsInClickedHex =
      gameBoard_->getHex(coord)->getPawns();
  std::vector<std::shared_ptr<Common::Pawn>> playerPawns;
  for (auto const &pawn : pawnsInClickedHex) {
    if (pawn->getPlayerId() == gameRunner_->currentPlayer()) {
      playerPawns.push_back(pawn);
    }
  }
  return playerPawns;
}

std::shared_ptr<Student::Player> GameExecuter::getCurrentPlayer() {
  for (auto player : playerVector_) {
    if (player->getPlayerId() == gameRunner_->currentPlayer()) {
      return player;
    }
  }
  return nullptr;
}

bool GameExecuter::isPlayerPawnsInHex(Common::CubeCoordinate coord) {
  std::vector<std::shared_ptr<Common::Pawn>> playerPawns =
      getPlayerPawnsInCoordinate(coord);
  return (playerPawns.size() != 0);
}

void GameExecuter::moveToNextPlayerTurn() {
  // jos vuorossa oleva pelaaja on viimeisenä
  std::shared_ptr<Player> currentPlayer = getCurrentPlayer();
  std::shared_ptr<Player> nextPlayer = nullptr;
  size_t currentPlayerIndex = std::distance(
      playerVector_.begin(),
      std::find(playerVector_.begin(), playerVector_.end(), currentPlayer));
  if (currentPlayerIndex == playerVector_.size() - 1) {
    nextPlayer = playerVector_.front();
  } else {
    nextPlayer = playerVector_.at(currentPlayerIndex + 1);
  }
  gameState_->changePlayerTurn(nextPlayer->getPlayerId());
  nextPlayer->setActionsLeft(3);
  userGuide_->setPlayerInTurn(nextPlayer);
} // namespace Student

void GameExecuter::doActionsOfAllActors() {
  std::vector<std::shared_ptr<Common::Actor>> allActors =
      gameBoard_->getAllActors();
  for (auto const &actor : allActors) {
    actor->doAction();
  }
}

void GameExecuter::updatePoints() {
  for (auto const &player : playerVector_) {
    player->addPoints(gameBoard_->getPlayerPawnAmount(player->getPlayerId()));
  }
  playerPointsWidget_->refreshPoints();
}

void GameExecuter::goToNextState() {
  switch (gameState_->currentGamePhase()) {
  case Common::GamePhase::MOVEMENT:
    gamePhaseToSinking();
    break;
  case Common::GamePhase::SINKING:
    gamePhaseToSpinning();
    break;
  case Common::GamePhase::SPINNING:
    gamePhaseToMovement();
    break;
  }
}

} // namespace Student
