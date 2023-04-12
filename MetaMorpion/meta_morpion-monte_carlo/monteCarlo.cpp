#include <stdio.h>
#include <iostream>
using namespace std;


/* Classe Grid (generique) */
class Grid{
  
} 

/* Classe Morpion (generique) */
class Morpion{
  

} 

/* Classe MetaMorpion (generique) */
class MetaMorpion{
  

} 


/* - Classe Position - */

public class Position{
  
  private int x;
  private int y;
  
  public:

  //contructeurs

  Position::Position() : x(0), y(0)
  {}
  
  Position::Position(double x, double y) : x(x), y(y)
  {}

  //getters et setters

  int getX(){

    return x;
  }

  int getY(){

    return y;
  }
}


/* - Classe Plateau Entier (Meta) - */

public class Board {

  //tableau contient la valeur de chaque case (-1 = X ; 0 = rien ; 1 = O ?)
  //sachant que ici "rien" veut dire que le morpion a l'interieur de cette case n'est pas termine
  int[][] boardValues;  //a changer en tableau simple pour gain de temps 



  public static final int DEFAULT_BOARD_SIZE = 3;

  public static final int IN_PROGRESS = -1;
  public static final int DRAW = 0;
  public static final int P1 = 1;
  public static final int P2 = 2;
  
  public:

  //contructeurs

  //getters et setters

  //methodes

  void refreshValues(){

    /* actualise les valeurs du meta morpion */
  }

  int checkStatus() {
    /* Evalue si le jeu est termine et renvoie le gagant,
    si c'est un draw renvoie 0, sinon renvoie -1 */ 

  }

  List<Position> getEmptyPositions() {

    int size = this.boardValues.length;
    List<Position> emptyPositions = new ArrayList<>();

    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {

        if (boardValues[i][j] == 0) emptyPositions.add(new Position(i, j));
      }
    }

    return emptyPositions;
  }
}


/* - Classe pour chaque Mini-Morpion - */

public class Meta {

  //tableau contient la valeur de chaque case (-1 = X ; 0 = rien ; 1 = O ?)
  int[][] boardValues; //a changer en tableau simple pour gain de temps 

  public static final int DEFAULT_BOARD_SIZE = 3;
  
  public static final int IN_PROGRESS = -1;
  public static final int DRAW = 0;
  public static final int P1 = 1;
  public static final int P2 = 2;
  
  public:

  //contructeurs

  //getters et setters

  //methodes

  void performMove(int player, Position p) {

    this.totalMoves++;
    boardValues[p.getX()][p.getY()] = player;
  }

  int checkStatus() {
    /* Evalue si le jeu est termine et renvoie le gagant,
    si c'est un draw renvoie 0, sinon renvoie -1 */ 

    /* Si on a une victoire: penser a actualiser la meta grille pour prendre en compte que cette grille a ete gagnee par un joueur */

  }

  List<Position> getEmptyPositions() {

    int size = this.boardValues.length;
    List<Position> emptyPositions = new ArrayList<>();

    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {

        if (boardValues[i][j] == 0) emptyPositions.add(new Position(i, j));
      }
    }

    return emptyPositions;
  }
}


/* - Classe Status - */

public class State {
    
  private Board board;
  private int playerNo;
  private int visitCount;
  private double winScore;

  public:

  //contructeurs

  State::State(Board board, int playerNo) : board(board), playerNo(playerNo), visitCount(0), winScore(0)
  {} 

  //getters et setters

  int getOpponent(){

    return 3-playerNo;
  }

  void setPlayerNo(int playerNo){

    this.playerNo = playerNo;
  }

  void setWinScore(int winScore){

    this.winScore = winScore;
  }
  
  //methodes

  void incrementVisit(){

    this.visitCount = this.visitCount + 1;
   }

   void addScore(int score){

    this.winScore = this.winScore + score;
   }

  List<State> getAllPossibleStates() {
    // construit une liste de tous les statuts possibles a partir du statut courant
      

  }

  void randomPlay() {
    /* recupere la liste de toutes les positions possibles sur le plateau
    et joue un coup aleatoire */
    List<Position> possiblePlay = board.getEmptyPositions();
    Position move;
    
    board.performMove(playerNo, move );
  }
}


/* - Classe Noeud - */

public class Node {

  private State state;
  private Node parent;
  private List<Node> childArray;
  
  public:

  //contructeurs

  Node::Node(State state, Node parent, List<Node> childArray) : state(state), parent(parent), childArray(childArray)
  {}

  Node::Node(State state) : state(state)
  {}

  Node::Node(Node node) : state(node.getState()), parent(node.getParent()), childArray(node.getChildArray())
  {}

  //getters et setters

  Node getParent(){
    
    return parent;
  }

  State getState(){
      
    return state;
  }

   List<Node> getChildArray(){

    return childArray;
  }

  void setParent(Node parent){
  
    this.parent = parent;
  }

  void setState(State state){
      
    this.state = state;
  }

  //methodes
 
}


/* - Classe Arbre - */

public class Tree {
  
  private Node root; 
    
  public:

  //contructeurs

  Tree::Tree(Node root): root(root)
  {}

  //getters et setters

  Node getRoot(){

    return root;
  }  

  void setRoot(Node root){

    this.root = root;
  }

  //methodes

}


/* - Classe Principale MCTS - */

public class MonteCarloTreeSearch {

  static final int WIN_SCORE = 10;
  int level;
  int opponent;


  public Board findNextMove(Board board, int playerNo) {
      // define an end time which will act as a terminating condition

    opponent = 3 - playerNo;

    Tree tree = new Tree();
    Node rootNode = tree.getRoot();

    rootNode.getState().setBoard(board);
    rootNode.getState().setPlayerNo(opponent);

    while (System.currentTimeMillis() < end) {
      
      Node promisingNode = selectPromisingNode(rootNode);
      
      if (promisingNode.getState().getBoard().checkStatus() == Board.IN_PROGRESS) {
        
        expandNode(promisingNode);
      }

      Node nodeToExplore = promisingNode;
      
      if (promisingNode.getChildArray().size() > 0) {
        
        nodeToExplore = promisingNode.getRandomChildNode();
      }

      int playoutResult = simulateRandomPlayout(nodeToExplore);
      backPropogation(nodeToExplore, playoutResult);
    }

    Node winnerNode = rootNode.getChildWithMaxScore();
    tree.setRoot(winnerNode);
    return winnerNode.getState().getBoard();
  }
}

//-------------------------SELECTION--------------------------------

private Node selectPromisingNode(Node rootNode) {

  Node node = rootNode;

  while (node.getChildArray().size() != 0) {

    node = UCT.findBestNodeWithUCT(node);
  }

  return node;
}



public class UCT {

  public static double uctValue(int totalVisit, double nodeWinScore, int nodeVisit){

    if (nodeVisit == 0) {
      
      return Integer.MAX_VALUE;
    }

    return ((double) nodeWinScore / (double) nodeVisit) + 1.41 * Math.sqrt(Math.log(totalVisit) / (double) nodeVisit);
  }

  public static Node findBestNodeWithUCT(Node node) {

    int parentVisit = node.getState().getVisitCount();

    return Collections.max(

      node.getChildArray(), 
      Comparator.comparing(
        c.uctValue(parentVisit, 
        c.getState().getWinScore(),
        c.getState().getVisitCount())
      )
    );
  }
}

//-------------------------EXPANSION--------------------------------

private void expandNode(Node node) {

  List<State> possibleStates = node.getState().getAllPossibleStates();
  
  possibleStates.forEach(state -> {
    
    Node newNode = new Node(state);
    newNode.setParent(node);
    newNode.getState().setPlayerNo(node.getState().getOpponent());
    node.getChildArray().add(newNode);
  });
}

//-------------------------SIMULATION------------------------------

private int simulateRandomPlayout(Node node) {
    
  Node tempNode = new Node(node);
  State tempState = tempNode.getState();

  int boardStatus = tempState.getBoard().checkStatus();

  if (boardStatus == opponent) {

    tempNode.getParent().getState().setWinScore(Integer.MIN_VALUE);
    return boardStatus;
  }

  while (boardStatus == Board.IN_PROGRESS) {

    tempState.togglePlayer();
    tempState.randomPlay();
    boardStatus = tempState.getBoard().checkStatus();
  }

  return boardStatus;
}

//----------------------BACKPROPAGATION----------------------------

private void backPropogation(Node nodeToExplore, int playerNo) {

  Node tempNode = nodeToExplore;

  while (tempNode != null) {

    tempNode.getState().incrementVisit();

    if (tempNode.getState().getPlayerNo() == playerNo) {

      tempNode.getState().addScore(WIN_SCORE);
    }
    
    tempNode = tempNode.getParent();
  }
}

//----------------------------------------------------------------


int main(){



    return 1;
}