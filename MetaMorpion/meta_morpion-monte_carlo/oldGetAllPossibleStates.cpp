// - construit une liste de tous les statuts possibles a partir du statut courant (tous les coups jouable par nous sur le plateau courant) -
    vector<State> getAllPossibleStates() {
        
        Morpion plateauAJouer = state.getBoard().getContainer().getValueXY(state.getBoard().getLastP().getX(),state.getBoard().getLastP().getY());
        
        vector<State> tempStateArray;

        // - Si le plateau dans lequel on doit joue est deja termine, alors on peut jouer n'importe ou -
        if(plateauAJouer.checkStatus() != -1){
        
        //    cerr<<"[Debug - getAllPossibleStates] Cas special: on joue dans n'importe quel moprion non-fini: "<<endl;
        
            // - On boucle tous les plateaux de morpion pour lister tous les coups possibles -            
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){

                    // - on ne selectionne que les morpions encore jouables (qui ne sont pas finis) -
                    if(state.getBoard().getContainer().getValueXY(i, j).checkStatus() == -1){
                        
                        // - on liste les Position ou on peut jouer dans la grille actuelle -
                        vector<Position> possiblePlay = state.getBoard().getContainer().getValueXY(i, j).getEmptyPositions();    
                        
                        // - on boucle pour chacun de ces coups -
                        for(int k = 0; k < possiblePlay.size(); k++){
                            
                            // - on creer un morpion temporaire pour chaque coup, pour cela on prend le morpion correspondant sur le metastate.getBoard() actuel et on y ajoute le "coup possible" actuel -
                            Morpion tempBoard = state.getBoard().getContainer().getValueXY(i, j);
                            tempBoard.getContainer().setValueXY(possiblePlay[k].getX(),possiblePlay[k].getY(), (3 - state.getPlayerNo()));

                            // - on creer un state temporaire avec le metaBoard actuel et on y ajoute notre tempMorp et update lastP, lastM -
                            State tempState = State(state.getBoard(), (3 - state.getPlayerNo()));

                            tempState.getBoard().getContainer().setValueXY(i, j, tempBoard);
                            tempState.getBoard().setLastM(Position(i, j));
                            tempState.getBoard().setLastP(possiblePlay[k]);

                            // - on ajoute ce state a notre liste -
                            tempStateArray.push_back(tempState);
                        }
                    }
                }
            }

        // - sinon on joue dans le plateau designe par lastPlayed (le dernier coup de l'adversaire) -
        }else{

            //cerr<<"[Debug - getAllPossibleStates] Cas normal: on joue dans focused morpion: "<<endl;

            // - on liste les Position ou on peut jouer dans la grille a jouer -
            vector<Position> possiblePlay = plateauAJouer.getEmptyPositions();    

            // - on boucle pour chacun de ces coups -
            for(int i = 0; i < possiblePlay.size(); i++){

                // - on creer un morpion temporaire correspondant a focused Morpion, auquel on y ajoute le "coup possible" actuel -

                Morpion tempBoard = plateauAJouer;
                
                tempBoard.getContainer().setValueXY(possiblePlay[i].getX(),possiblePlay[i].getY(), (3 - state.getPlayerNo()));
            
                // - on creer un state temporaire avec le metaBoard actuel et on y ajoute notre tempMorp et on update lastP et last M -
                State tempState = State(state.getBoard(), (3 - state.getPlayerNo())); 
                
                tempState.getBoard().getContainer().setValueXY(state.getBoard().getLastP().getX(),state.getBoard().getLastP().getY(), tempBoard);
               
                tempState.getBoard().setLastM(state.getBoard().getLastP());
                tempState.getBoard().setLastP(possiblePlay[i]);

                // - on ajoute ce state a notre liste -
                tempStateArray.push_back(tempState);
            }

          //  cerr<<"[Debug - getAllPossibleStates] Fin de la fonction "<<endl;
        }

        // - on renvoie la liste de State calculee -
        return tempStateArray;
    }