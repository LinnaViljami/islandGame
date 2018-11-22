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
    SpinnerContainerWidget *spinnerWidget,
    std::vector<std::shared_ptr<Student::Player>> playerVector,
    Student::UserGuideWidget *userGuide, PlayerPointsWidget *playerPointsWidget)
    : gameRunner_(gameRunner), gameBoard_(gameBoard), gameState_(gameState),
      spinnerWidget_(spinnerWidget), playerVector_(playerVector),
      userGuide_(userGuide), playerPointsWidget_(playerPointsWidget),
      selectedHexCoordinates_(Common::CubeCoordinate()), isHexSelected_(false),
      isWheelSpun_(false), selectedActorId_(-1),
      movesOfSpunActor_(std::string()) {

  connect(gameBoard_->getBoardWidget(), &GameBoardWidget::hexClicked, this,
          &GameExecuter::handleHexClick);
  connect(spinnerWidget_, &SpinnerContainerWidget::spinningFinished, this,
          &GameExecuter::handleSpin);
  gameState->changePlayerTurn(1);
  gameState->changeGamePhase(Common::GamePhase::MOVEMENT);
  userGuide_->setPlayerInTurn(getCurrentPlayer());
  userGuide->setNextActionGuide("Aloita klikkaamalla ruutua josta haluat siirtää nappulan");
  userGuide_->setAdditionalMessage("Tervetuloa pelaamaan LoveIsland Suomi 2018-peliä!");
}

void GameExecuter::handleHexClick(Common::CubeCoordinate coordinates) {
  switch (gameState_->currentGamePhase()) {
  case Common::GamePhase::MOVEMENT:
    handlePhaseMovement(coordinates);
    break;
  case Common::GamePhase::SINKING:
    handlePhaseSinking(coordinates);
    break;
  case Common::GamePhase::SPINNING:
    handlePhaseSpinning(coordinates);
    break;
  }
  gameBoard_->getBoardWidget()->updateBoard();
}

void GameExecuter::handlePhaseMovement(Common::CubeCoordinate coord) {
  std::shared_ptr<Common::Hex> clickedHex = gameBoard_->getHex(coord);

  if (clickedHex == nullptr) {
    userGuide_->setAdditionalMessage("Virhe pelissä! "
                                     "Klikkaamaasi ruutua ei ole olemassa, älä ota yhteyttä kehittäjiin vaan pure hammasta!"
                                     " tai käynnistä peli uudelleen");
  } else if (!isHexSelected_) {
    if (isPlayerPawnsInHex(coord)) {
      selectedHexCoordinates_ = coord;
      isHexSelected_ = true;
      userGuide_->setAdditionalMessage("Ruutu valittu!");
      userGuide_->setNextActionGuide("Valitse ruutu johon haluat liikuttaa nappulan.");
    }
    else{
        userGuide_->setAdditionalMessage("Et voi valita ruutua, jossa sinulla ei ole yhtään nappia.");
    }
  } else if (isHexSelected_) {
    if (selectedHexCoordinates_.operator==(coord)) {
      isHexSelected_ = false;
      userGuide_->setAdditionalMessage("Valinta poistettu klikkaamastasi ruudusta.");
      userGuide_->setNextActionGuide("Valitse ruutu josta haluat liikuttaa nappulan.");
    } else {
      tryMovePawn(coord);
    }
  }
  if (getCurrentPlayer()->getActionsLeft() == 0) {
    gameState_->changeGamePhase(Common::GamePhase::SINKING);
    userGuide_->setNextActionGuide("Valitse upotettava ruutu.");
    userGuide_->setAdditionalMessage("Liikkusi loppuivat, pelivaihe on nyt upotus.");
  }
}

void GameExecuter::handlePhaseSinking(Common::CubeCoordinate coord) {
  if (tryFlipTile(coord)) {
    gamePhaseToSpinning();
  }
}

void GameExecuter::handlePhaseSpinning(Common::CubeCoordinate coord) {
  if (!isWheelSpun_) {
      userGuide_->setAdditionalMessage("Kiekko ei ollut vielä pyörähtänyt, odota että se pyörähtää loppuun.");
    return;
  }
  if (!isHexSelected_) {
    if (trySelectActor(typeOfSpunActor_, coord)) {
      selectedHexCoordinates_ = coord;
      userGuide_->setAdditionalMessage("Toimija valittu.");
      userGuide_->setNextActionGuide("Klikkaa ruutua, johon haluat siirtää toimijan.");
      isHexSelected_ = true;
      return;
    } else if (trySelectTransport(typeOfSpunActor_, coord)) {
      selectedHexCoordinates_ = coord;
      userGuide_->setAdditionalMessage("Kuljettaja valittu.");
      userGuide_->setNextActionGuide("Klikkaa ruutua, johon haluat siirtää kuljettajan.");
      isHexSelected_ = true;
      return;
    }
    userGuide_->setAdditionalMessage("Et voi valita toimijaa/kuljettajaa kyseisessä ruudussa");
    userGuide_->setNextActionGuide("Yritä valita toimija/kuljettaja toisesta ruudusta");
    return;
  }

  if (selectedHexCoordinates_.operator==(coord)) {
    isHexSelected_ = false;
    userGuide_->setAdditionalMessage("Ei ruutua valittuna.");
    userGuide_->setNextActionGuide("Valitse ruutu josta liikutat toimijaa/kuljettajaa");
    return;
  }

  if (tryMoveActor(coord)) {
    tryDoActor(typeOfSpunActor_, coord);
    gamePhaseToMovement();
    userGuide_->setAdditionalMessage("Liikutit toimijan ja se toteutti toimintonsa!");

    return;
  }

  if (tryMoveTransport(coord)) {
    gamePhaseToMovement();
    userGuide_->setAdditionalMessage("Liikutit kuljettajan ja siinä olevat napit!");
    return;
  }
  else{
      userGuide_->setAdditionalMessage("Et voi liikuttaa toimijaa/kuljettajaa klikkaamaasi ruutuun");
  }
}

void GameExecuter::handleSpin() {
    isWheelSpun_ = true;
    userGuide_->setNextActionGuide("Valitse toimija, jota haluat liikuttaa.");
    userGuide_->setAdditionalMessage("Kiekko pyörähti, näet siitä minkä tyyppistä toimijaa sinun tulee liikuttaa.");
}

bool GameExecuter::trySelectActor(std::string actorType,
                                  Common::CubeCoordinate coord) {
  for (auto const &a : gameBoard_->getHex(coord)->getActors()) {
    if (a->getActorType() == actorType) {
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
  std::shared_ptr<Common::Hex> selectedHex =
      gameBoard_->getHex(selectedHexCoordinates_);
  std::shared_ptr<Common::Hex> clickedHex = gameBoard_->getHex(to);

  std::vector<std::shared_ptr<Common::Transport>> hexTransports =
      selectedHex->getTransports();
  if (hexTransports.size() != 0) {
    for (auto const &transport : hexTransports) {
      if (transport->canMove(getCurrentPlayer()->getPlayerId())) {
        gameBoard_->moveTransport(transport->getId(), to);
        return true;
      }
    }
  }
  return false;
}

bool GameExecuter::tryFlipTile(Common::CubeCoordinate coord) {
  std::shared_ptr<Common::Hex> clickedHex = gameBoard_->getHex(coord);
  try {
    std::string actor = gameRunner_->flipTile(coord);
    // if was actor in clicked hex and it can do
    if (tryDoActor(actor, coord)) {
        userGuide_->setAdditionalMessage("Ruutu upotettu, toimija teki toimintonsa!");
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
  userGuide_->setNextActionGuide("Valitse liikutettava nappula klikkaamalla ruutua");
  nextTurn();
}

void GameExecuter::gamePhaseToSpinning() {
  isWheelSpun_ = false;
  isHexSelected_ = false;
  gameState_->changeGamePhase(Common::GamePhase::SPINNING);
  std::pair<std::string, std::string> spinResult = gameRunner_->spinWheel();
  typeOfSpunActor_ = spinResult.first;
  movesOfSpunActor_ = spinResult.second;
  spinnerWidget_->beginSpin(spinResult.first, spinResult.second);
  if (!gameBoard_->isAnyActorsOrTransportsOfType(typeOfSpunActor_)) {
    gamePhaseToMovement();
    userGuide_->setAdditionalMessage("Laudalla ei ole käännettynä yhtään kiekon arpomaa toimijaa. Vuoro siirtyi seuraavalle pelaajalle.");
    return;
  }
  userGuide_->setNextActionGuide("Odota, että kiekko pyörähtää.");
}

void GameExecuter::tryMovePawn(Common::CubeCoordinate to) {
  std::vector<std::shared_ptr<Common::Pawn>> playerPawnsInSelected =
      getPlayerPawnsInCoordinate(selectedHexCoordinates_);
  if (playerPawnsInSelected.size() != 0) {
    try {
      getCurrentPlayer()->setActionsLeft(gameRunner_->movePawn(
          selectedHexCoordinates_, to, playerPawnsInSelected.front()->getId()));
      userGuide_->setAdditionalMessage("Nappula liikutettu onnistuneesti.");
      userGuide_->setNextActionGuide("Valitse ruutu josta haluat liikuttaa nappulan.");
    } catch (Common::IllegalMoveException) {
        userGuide_->setAdditionalMessage("Et voi liikuttaa nappulaa klikkaamaasi ruutuun!");
        userGuide_->setNextActionGuide("Valitse uudelleen ruutu josta haluat liikuttaa nappulan.");
    }
  }
  else{
      userGuide_->setAdditionalMessage("Valitsemassasi ruudussa ei ole yhtään nappulaa joita voisit liikuttaa, valinta poistettu");
  }
  isHexSelected_ = false;
}

bool GameExecuter::putPawnsToTransport(std::string type,
                                       Common::CubeCoordinate coord) {
  std::shared_ptr<Common::Hex> hexInCoord = gameBoard_->getHex(coord);
  for (auto const &t : hexInCoord->getTransports()) {
    if (t->getTransportType() == type) {
      for (auto const &pawn : hexInCoord->getPawns()) {
        t->addPawn(pawn);
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
    if (pawn->getPlayerId() == gameState_->currentPlayer()) {
      playerPawns.push_back(pawn);
    }
  }
  return playerPawns;
}

std::shared_ptr<Student::Player> GameExecuter::getCurrentPlayer() {
  for (auto player : playerVector_) {
    if (player->getPlayerId() == gameState_->currentPlayer()) {
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

void GameExecuter::nextTurn() {
  if (playerVector_.back()->getPlayerId() ==
      getCurrentPlayer()->getPlayerId()) {
    gameState_->changePlayerTurn(playerVector_.front()->getPlayerId());
    playerVector_.front()->setActionsLeft(3);
    userGuide_->setPlayerInTurn(getCurrentPlayer());
    return;
  }
  for (size_t t = 0; t < playerVector_.size() - 1; ++t) {
    int i = static_cast<int>(t);
    if (playerVector_.at(i)->getPlayerId() ==
        getCurrentPlayer()->getPlayerId()) {
      gameState_->changePlayerTurn(playerVector_.at(i + 1)->getPlayerId());
      userGuide_->setPlayerInTurn(getCurrentPlayer());
      playerVector_.at(i + 1)->setActionsLeft(3);
      return;
    }
  }
}

} // namespace Student
