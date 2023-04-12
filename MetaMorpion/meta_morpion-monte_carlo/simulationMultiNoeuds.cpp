int simulateRandomPlayout(shared_ptr<Node> node) {
    
    // - On initialise le statut actuel du noeud, statut que l'on va actualiser en simulant la partie petit a petit -
    Morpion morpAJouer = node->getState().getBoard().getContainer().getValueXY(node->getState().getBoard().getLastP().getX(), node->getState().getBoard().getLastP().getY());
    int boardStatus = morpAJouer.checkStatus();

   
    // - si node est DEJA une partie terminee et que celle-ci est PERDANTE, on met le winscore a une valeur tres faible et on renvoi le status -
    if (boardStatus == 2) {

        node->getState().setWinScore(-10);
        return boardStatus;
    }


    // - sinon, on se lance dans la simulation dans une copie de root jusqu'a ce que la partie soit terminee -
    shared_ptr<Node> nodeParentASimuler = make_shared<Node>(node->getState());
           

    while (boardStatus == -1) {

        // - On creer un nouveau noeud pour le prochain coup a generer (copie de son parent) -
        shared_ptr<Node> noeudCoupSuivant = make_shared<Node>(noeudParentARelier->getState());
        
        // - On le rattache au noeud du coup precedent (parent) -
        noeudCoupSuivant->setParent(noeudParentARelier);             
        noeudParentARelier->getChildArray().push_back(noeudCoupSuivant);

        // - On change le joueur qui va jouer, et on genere un coup aleatoire -
        noeudCoupSuivant->getState().togglePlayer();
        Morpion &selectedMorpion = noeudCoupSuivant->getState().getBoard().getContainer().getValueXY(noeudParentARelier->getState().getBoard().getLastP().getX(), noeudParentARelier->getState().getBoard().getLastP().getY());
        noeudCoupSuivant->randomPlay(selectedMorpion);   

        // - On update la variable status -
        boardStatus = noeudCoupSuivant->getState().getBoard().checkStatus();

        // - On change le noeudParent par le noeud courant -
        noeudParentARelier = noeudCoupSuivant;
    }

    cerr << "fin de la simulation" << endl;


    // - On supprime tous les fils de node car on a finit la simulation, on a plus besoin d'eux -
    node->getChildArray().clear();

    // - on renvoie le statut de la partie -
    return boardStatus;
}