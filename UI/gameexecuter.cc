#include "gameexecuter.hh"
#include "actor.hh"
#include "gameexception.hh"
#include <QDebug>
#include <iostream>
#include <vector>
#include "illegalmoveexception.hh"
#include <algorithm>

namespace Student {

GameExecuter::GameExecuter(
    std::shared_ptr<Common::IGameRunner> gameRunner,
    std::shared_ptr<GameBoard> gameBoard, std::shared_ptr<GameState> gameState,
    SpinnerContainerWidget *spinnerWidget,
    std::vector<std::shared_ptr<Common::IPlayer>> playerVector,
    std::shared_ptr<QLabel> userGuideText)
    : gameRunner_(gameRunner), gameBoard_(gameBoard), gameState_(gameState),
      spinnerWidget_(spinnerWidget), playerVector_(playerVector), userGuideText_(userGuideText),
      selectedHexCoordinates_(Common::CubeCoordinate()), isHexSelected_(false),
      isWheelSpun_(false), selectedActorId_(-1), movesOfSpunActor_(std::string())
{

  connect(gameBoard_->getBoardWidget(), &GameBoardWidget::hexClicked, this,
          &GameExecuter::handleHexClick);
  connect(spinnerWidget_, &SpinnerContainerWidget::spinningFinished, this,
          &GameExecuter::handleSpin);
  gameState->changePlayerTurn(1);
  gameState->changeGamePhase(Common::GamePhase::MOVEMENT);

  userGuideText->setText("Tervetuloa pelaamaan Loveisland Suomi 2018!<br>"
                         "Klikkaa aluksi ruutua josta haluat siirtää napin");

}



void GameExecuter::handleHexClick(Common::CubeCoordinate coordinates) {
    switch (gameState_->currentGamePhase()) {
        case Common::GamePhase::MOVEMENT :
            handlePhaseMovement(coordinates);
        break;
        case Common::GamePhase::SINKING :
            handlePhaseSinking(coordinates);
        break;
        case Common::GamePhase::SPINNING :
            handlePhaseSpinning(coordinates);
        break;
    }
    gameBoard_->getBoardWidget()->updateBoard();
}

void GameExecuter::handlePhaseMovement(Common::CubeCoordinate coord)
{
    std::shared_ptr<Common::Hex> clickedHex = gameBoard_->getHex(coord);

    if (clickedHex == nullptr) {
      throw Common::GameException(
          "Clicked hex not exist in game-executer gameboard_");
    } else if (!isHexSelected_) {
        if (isPlayerPawnsInHex(coord)) {
        selectedHexCoordinates_ = coord;
        isHexSelected_ = true;
        }
    }
    else if (isHexSelected_) {
        if (selectedHexCoordinates_.operator==(coord)) {
            isHexSelected_ = false;
        }
        else {
            //TODO: Player must able to choose if he move transport or only pawns
            //Current implement try first move actor, then pawns if actor cant move
            if(!tryMoveTransport(coord)){
                tryMovePawn(coord);
            }
        }
    }
    if (getCurrentPlayer()->getActionsLeft()==0) {
      gameState_->changeGamePhase(Common::GamePhase::SINKING);
    }
}

void GameExecuter::handlePhaseSinking(Common::CubeCoordinate coord)
{
    if(tryFlipTile(coord)){
        gamePhaseToSpinning();
    }
}

void GameExecuter::handlePhaseSpinning(Common::CubeCoordinate coord)
{
    if(!isWheelSpun_) {
        userGuideText_->setText("Spinneri ei ollut vielä pyörähtänyt<br>"
                                "Valitse ruutu josta haluat aktorin/transportin siirtyvän");
        return;
    }

    if (!isHexSelected_) {
        if(trySelectActor(typeOfSpunActor_, coord)){
            selectedHexCoordinates_ = coord;
            userGuideText_->setText("Aktori valittu.<br>"
                                    "Klikkaa ruutua johon haluat siirtää aktorin");
            isHexSelected_ = true;
            return;
        }
        else if(trySelectTransport(typeOfSpunActor_, coord)){
            selectedHexCoordinates_ = coord;
            userGuideText_->setText("Transport valittu.<br>"
                                    "Klikkaa ruutua johon haluat siirtää transportin");
            isHexSelected_ = true;
            return;
        }
        userGuideText_->setText("Et voi valita aktoria/transporttia klikkaamassasi ruudussa");
        return;
    }

    if (selectedHexCoordinates_.operator==(coord)) {
        isHexSelected_ = false;
        qDebug() << "Valitse ruutu";
        return;
    }

    if (tryMoveActor(coord)){
        tryDoActor(typeOfSpunActor_, coord);
        gamePhaseToMovement();
        qDebug() << "Aktori liikutettu, toiminto toteutettu ja pelitilaksi vaihdettu movement, vuorossa oleva pelaaja vaihtui";
        return;
    }

    if(tryMoveTransport(coord)){
        gamePhaseToMovement();
        qDebug() << "Transport liikutettu, pelitilaksi vaihdettu movement, vuorossa oleva pelaaja vaihtui";
        return;
    }
    qDebug() << "Et voi liikuttaa aktoria/transporttia valitsemaasi ruutuun";
}

void GameExecuter::handleSpin() {
    isWheelSpun_ = true;
}


bool GameExecuter::trySelectActor(std::string actorType,
                                  Common::CubeCoordinate coord) {
  for (auto const &a : gameBoard_->getHex(coord)->getActors()) {
    if (a->getActorType() == actorType) {
      selectedActorId_ = a->getId();
      return true;;
    }
  }
  selectedActorId_ = -1;
  return false;
}

bool GameExecuter::trySelectTransport(std::string type, Common::CubeCoordinate coord)
{
    for(auto const &t : gameBoard_->getHex(coord)->getTransports()){
        if(t->getTransportType() == type){
            selectedActorId_ = t->getId();
            return true;
        }
    }
    selectedActorId_ = -1;
    return false;
}

bool GameExecuter::tryMoveActor(Common::CubeCoordinate to)
{
    if(gameRunner_->checkActorMovement(selectedHexCoordinates_, to, selectedActorId_, movesOfSpunActor_)){
        gameRunner_->moveActor(selectedHexCoordinates_, to, selectedActorId_, movesOfSpunActor_);
        return true;
    }
    return false;
}

bool GameExecuter::tryMoveTransport(Common::CubeCoordinate to)
{
    std::shared_ptr<Common::Hex> selectedHex = gameBoard_->getHex(selectedHexCoordinates_);
    std::shared_ptr<Common::Hex> clickedHex = gameBoard_->getHex(to);

    std::vector<std::shared_ptr<Common::Transport>> hexTransports = selectedHex->getTransports();
    if(hexTransports.size()!=0){
        for(auto const& transport : hexTransports){
            if(transport->canMove(getCurrentPlayer()->getPlayerId())){
                gameBoard_->moveTransport(transport->getId(), to);
                return true;
            }
        }
    }
    return false;
}

bool GameExecuter::tryFlipTile(Common::CubeCoordinate coord)
{
    std::shared_ptr<Common::Hex> clickedHex = gameBoard_->getHex(coord);
    try{
        std::string actor = gameRunner_->flipTile(coord);
        //if was actor in clicked hex and it can do
        if(tryDoActor(actor, coord)){
            return true;
        }
        //if was transport in clicked hex
        if(putPawnsToTransport(actor, coord)){
            return true;
        }
    }
    catch(Common::IllegalMoveException& e){
        qDebug() << "Et voi kääntää klikkaamaasi ruutua";
        return false;
    }
    return false;
}

bool GameExecuter::tryDoActor(std::string type, Common::CubeCoordinate coord)
{
    std::shared_ptr<Common::Hex> hexInCoord = gameBoard_->getHex(coord);
    for (auto const &a : hexInCoord->getActors()) {
        if (a->getActorType() == type) {
        a->doAction();
        gamePhaseToSpinning();
        return true;
        }
    }
    return false;
}

void GameExecuter::gamePhaseToMovement()
{
    isWheelSpun_ = false;
    isHexSelected_ = false;
    gameState_->changeGamePhase(Common::GamePhase::MOVEMENT);
    qDebug() << "Pelitilaksi vaihdettu Movement";
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
  if(!gameBoard_->isAnyActorsOrTransportsOfType(typeOfSpunActor_)){
      gamePhaseToMovement();
      return;
  }
}

void GameExecuter::tryMovePawn(Common::CubeCoordinate to) {
  std::vector<std::shared_ptr<Common::Pawn>> playerPawnsInSelected =
      getPlayerPawnsInCoordinate(selectedHexCoordinates_);
  if (playerPawnsInSelected.size() != 0) {
      try{
        getCurrentPlayer()->setActionsLeft(gameRunner_->movePawn(selectedHexCoordinates_,
                                                                 to, playerPawnsInSelected.front()->getId()));
      }
      catch(Common::IllegalMoveException){
          qDebug() << "Pawn cannot move to clicked hex";
      }
  }
  isHexSelected_ = false;
}

bool GameExecuter::putPawnsToTransport(std::string type, Common::CubeCoordinate coord)
{
    std::shared_ptr<Common::Hex> hexInCoord = gameBoard_->getHex(coord);
    for (auto const &t : hexInCoord->getTransports()){
        if(t->getTransportType() == type){
            for(auto const &pawn : hexInCoord->getPawns()){
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

std::shared_ptr<Common::IPlayer> GameExecuter::getCurrentPlayer() {
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

void GameExecuter::nextTurn()
{
    qDebug() << "Vuoro vaihdettu seuraavalle pelaajalle";
    if (playerVector_.back()->getPlayerId()==getCurrentPlayer()->getPlayerId()){
        gameState_->changePlayerTurn(playerVector_.front()->getPlayerId());
        playerVector_.front()->setActionsLeft(3);
        return;
    }
    for(size_t t = 0; t < playerVector_.size()-1; ++t){
        int i = static_cast<int>(t);
        if(playerVector_.at(i)->getPlayerId()==getCurrentPlayer()->getPlayerId()){
            gameState_->changePlayerTurn(playerVector_.at(i+1)->getPlayerId());
            playerVector_.at(i+1)->setActionsLeft(3);
            return;
        }
    }
}


} // namespace Student
