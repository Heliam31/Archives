
/* 
TUPLES POUR LES DIFFERENTES RELATIONS.
Attention les valeurs sont rentrées en majuscule et il n'y a pas d'accents
*/

/*
Pour mettre les dates au format date avec numero jj-mm-aaaa
*/

ALTER session SET NLS_DATE_FORMAT='DD-MM-YYYY' ; 

/* 
Paramètres d'affichage
*/




SET PAGESIZE 30
COLUMN COLUMN_NAME FORMAT A30
SET LINESIZE 300
/*
Effacer les anciennes valeurs des relations
*/

prompt -------------------------------------------;
prompt --- Suppression des anciens tuples --------;
prompt -------------------------------------------;
DELETE FROM EMPRUNT; 
DELETE FROM CARACTERISE; 
DELETE FROM MOT_CLEF; 
DELETE FROM EXEMPLAIRE; 
DELETE FROM ABONNE; 
DELETE FROM LIVRE; 
/*
Insertion des tuples dans les relations
*/

prompt -------------------------------------------;
prompt --- Insertion des nouveaux tuples ---------;
prompt -------------------------------------------;

prompt ------------------------------------------;
prompt -----     insertion abonne    ------------;
prompt ------------------------------------------;

INSERT INTO ABONNE VALUES (901001,'LEVEQUE','PIERRE','MONTPELLIER',40,500,NULL) ; 
INSERT INTO ABONNE VALUES (902043,'DUPONT','MARIE','MONTPELLIER',20,200,20); 
INSERT INTO ABONNE VALUES (902075,'RENARD','ALBERT','MONTPELLIER',18,200,NULL); 
INSERT INTO ABONNE VALUES (911007,'MARTIN','LOIC','BEZIERS',35,500,20); 
INSERT INTO ABONNE VALUES (911021,'DUPONT','ANTOINE','MONTPELLIER',38,500,NULL ); 
INSERT INTO ABONNE VALUES (911022,'DUPONT','SYLVIE','MONTPELLIER',35,500,NULL); 
INSERT INTO ABONNE VALUES (911023,'DUPONT','JEAN','MONTPELLIER',22,200,20); 
INSERT INTO ABONNE VALUES (922016,'MEUNIER','LUC','MONTPELLIER',14,100,NULL); 
INSERT INTO ABONNE VALUES (921102,'LUCAS','PAUL','MONTPELLIER',48,500,20); 
INSERT INTO ABONNE VALUES (922143,'REVEST','ANNIE','MONTPELLIER',12,100,NULL); 
INSERT INTO ABONNE VALUES (932010,'ANTON','JEANNE','MONTPELLIER',10,100,NULL); 


prompt ------------------------------------------;
prompt -----     insertion livre     ------------;
prompt ------------------------------------------;


INSERT INTO LIVRE VALUES ('1_104_1050_2','LE MUR',20,'NOUVELLE'); 
INSERT INTO LIVRE VALUES ('0_15_270500_3','LE MIRACLE DE LA ROSE',20,'ROMAN'); 
INSERT INTO LIVRE VALUES ('0_85_4107_3','L ENFANT',19,'ROMAN'); 
INSERT INTO LIVRE VALUES ('0_112_3785_5','POESIES COMPLETES', 15,'POEME'); 
INSERT INTO LIVRE VALUES ('0_201_14439_5','AN INTRODUCTION TO DATABASE SYSTEMS',20,'SCIENCES'); 
INSERT INTO LIVRE VALUES ('0_12_27550_2','NEW APPLICATIONS OF DATABASES',20,'SCIENCES'); 
INSERT INTO LIVRE VALUES ('0_8_7707_2','BASES DE DONNEES RELATIONNELLES',20,'SCIENCES'); 
INSERT INTO LIVRE VALUES ('1_22_1721_3','LE NOM DE LA ROSE',20,'ROMAN'); 
INSERT INTO LIVRE VALUES ('3_505_13700_5','LE GRAND VESTIAIRE',20,'ROMAN'); 
INSERT INTO LIVRE VALUES ('0_18_47892_2','UNE ROSE POUR MORRISSON',20,'ROMAN'); 
INSERT INTO LIVRE VALUES ('9_782070_36','LA PERLE',20,'ROMAN'); 
INSERT INTO LIVRE VALUES ('2_7296_0040','GODEL ESCHER BACH : LES BRINS D UNE GUIRLANDE',20,'HISTOIRE'); 
INSERT INTO LIVRE VALUES ('0_26_28079_6','FUNDAMENTALS OF DATABASE SYSTEMS',20,'SCIENCES'); 


prompt ------------------------------------------;
prompt -----     insertion MOT_CLEF  ------------;
prompt ------------------------------------------;


INSERT INTO MOT_CLEF VALUES ('LITTERATURE'); 
INSERT INTO MOT_CLEF VALUES ('ROMAN'); 
INSERT INTO MOT_CLEF VALUES ('POESIE'); 
INSERT INTO MOT_CLEF VALUES ('SCIENCES'); 
INSERT INTO MOT_CLEF VALUES ('INFORMATIQUE'); 
INSERT INTO MOT_CLEF VALUES ('BASES DE DONNEES'); 
INSERT INTO MOT_CLEF VALUES ('HISTOIRE'); 
INSERT INTO MOT_CLEF VALUES ('ESSAI'); 
INSERT INTO MOT_CLEF VALUES ('NOUVELLE'); 
INSERT INTO MOT_CLEF VALUES ('MEDECINE'); 
INSERT INTO MOT_CLEF VALUES ('SQL'); 


prompt ------------------------------------------;
prompt -----     insertion CARACTERISE   --------;
prompt ------------------------------------------;


INSERT INTO CARACTERISE VALUES ('1_104_1050_2','LITTERATURE'); 
INSERT INTO CARACTERISE VALUES ('0_15_270500_3','LITTERATURE'); 
INSERT INTO CARACTERISE VALUES ('0_15_270500_3','ROMAN'); 
INSERT INTO CARACTERISE VALUES ('0_85_4107_3','LITTERATURE'); 
INSERT INTO CARACTERISE VALUES ('0_85_4107_3','ROMAN'); 
INSERT INTO CARACTERISE VALUES ('0_112_3785_5','LITTERATURE'); 
INSERT INTO CARACTERISE VALUES ('0_112_3785_5','POESIE'); 
INSERT INTO CARACTERISE VALUES ('0_201_14439_5','SCIENCES'); 
INSERT INTO CARACTERISE VALUES ('0_201_14439_5','INFORMATIQUE'); 
INSERT INTO CARACTERISE VALUES ('0_201_14439_5','BASES DE DONNEES'); 
INSERT INTO CARACTERISE VALUES ('0_12_27550_2','SCIENCES');
INSERT INTO CARACTERISE VALUES ('0_12_27550_2','INFORMATIQUE'); 
INSERT INTO CARACTERISE VALUES ('0_8_7707_2','SCIENCES'); 
INSERT INTO CARACTERISE VALUES ('0_8_7707_2','INFORMATIQUE'); 
INSERT INTO CARACTERISE VALUES ('0_8_7707_2','BASES DE DONNEES'); 
INSERT INTO CARACTERISE VALUES ('1_22_1721_3','ROMAN'); 
INSERT INTO CARACTERISE VALUES ('1_22_1721_3','HISTOIRE'); 
INSERT INTO CARACTERISE VALUES ('3_505_13700_5','LITTERATURE'); 
INSERT INTO CARACTERISE VALUES ('3_505_13700_5','ROMAN'); 
INSERT INTO CARACTERISE VALUES ('0_26_28079_6','SCIENCES'); 
INSERT INTO CARACTERISE VALUES ('0_26_28079_6','INFORMATIQUE'); 
INSERT INTO CARACTERISE VALUES ('0_26_28079_6','BASES DE DONNEES'); 
INSERT INTO CARACTERISE VALUES ('0_26_28079_6','SQL');


prompt ------------------------------------------;
prompt -----     insertion EXEMPLAIRE  ----------;
prompt ------------------------------------------;





INSERT INTO EXEMPLAIRE VALUES (1010, '10-04-2015',55,'EMPRUNTABLE','BON','0_18_47892_2'); 
INSERT INTO EXEMPLAIRE VALUES (1011, '10-04-2015',55,'EMPRUNTABLE','BON','0_18_47892_2'); 
INSERT INTO EXEMPLAIRE VALUES (1012, '20-05-2015',112,'EMPRUNTABLE','BON','3_505_13700_5'); 
INSERT INTO EXEMPLAIRE VALUES (2909, '30-03-2017',35,'EMPRUNTABLE','BON','3_505_13700_5'); 
INSERT INTO EXEMPLAIRE VALUES (2673, '15-03-2018',42,'EMPRUNTABLE','ABIME','3_505_13700_5'); 
INSERT INTO EXEMPLAIRE VALUES (2710, '20-06-2014',27,'CONSULTABLE','BON','0_8_7707_2'); 
INSERT INTO EXEMPLAIRE VALUES (2711, '20-06-2014',27,'EMPRUNTABLE','BON','0_8_7707_2'); 
INSERT INTO EXEMPLAIRE VALUES (3014, '15-09-2017',42,'CONSULTABLE','BON','0_201_14439_5'); 
INSERT INTO EXEMPLAIRE VALUES (3016, '15-09-2017',42,'EMPRUNTABLE','BON','0_201_14439_5'); 
INSERT INTO EXEMPLAIRE VALUES (3702, '20-02-2019',21,'EMPRUNTABLE','BON','1_22_1721_3'); 
INSERT INTO EXEMPLAIRE VALUES (3703, '20-02-2019',21,'CONSULTABLE','BON','1_22_1721_3'); 
INSERT INTO EXEMPLAIRE VALUES (4111, '03-01-2021',48,'EMPRUNTABLE','BON','1_22_1721_3'); 
INSERT INTO EXEMPLAIRE VALUES (4112, '03-01-2021',48,'EXCLU','BON','1_22_1721_3'); 
INSERT INTO EXEMPLAIRE VALUES (4203, '29-11-2019',35,'EMPRUNTABLE','BON','1_104_1050_2'); 
INSERT INTO EXEMPLAIRE VALUES (4204, '29-11-2019',35,'EMPRUNTABLE','ABIME','1_104_1050_2'); 
INSERT INTO EXEMPLAIRE VALUES (5003, '10-06-2020',39,'EMPRUNTABLE','BON','1_104_1050_2'); 
INSERT INTO EXEMPLAIRE VALUES (5004, '10-06-2020',41,'EMPRUNTABLE','BON','0_15_270500_3'); 
INSERT INTO EXEMPLAIRE VALUES (5005, '10-06-2020',41,'EMPRUNTABLE','BON','0_15_270500_3'); 
INSERT INTO EXEMPLAIRE VALUES (5103, '20-12-2017',47,'CONSULTABLE','BON','0_12_27550_2'); 
INSERT INTO EXEMPLAIRE VALUES (5104, '20-12-2017',47,'EMPRUNTABLE','BON','0_12_27550_2'); 
INSERT INTO EXEMPLAIRE VALUES (6006, '15-02-2021',33,'EMPRUNTABLE','BON','0_85_4107_3'); 
INSERT INTO EXEMPLAIRE VALUES (6007, '15-02-2021',33,'EMPRUNTABLE','BON','0_85_4107_3'); 
INSERT INTO EXEMPLAIRE VALUES (5202, '18-10-2020',40,'EMPRUNTABLE','BON','0_18_47892_2'); 
INSERT INTO EXEMPLAIRE VALUES (7000, '01-09-2016',42,'CONSULTABLE','BON','2_7296_0040'); 
INSERT INTO EXEMPLAIRE VALUES (7001, '01-09-2016',42,'EMPRUNTABLE','BON','2_7296_0040'); 
INSERT INTO EXEMPLAIRE VALUES (7002, '01-09-2016',42,'EXCLU','BON','2_7296_0040'); 
INSERT INTO EXEMPLAIRE VALUES (1090, '23-11-2015',15,'EXCLU','ABIME','9_782070_36'); 
INSERT INTO EXEMPLAIRE VALUES (1091, '23-11-2015',150,'CONSULTABLE','EN_REPARATION','9_782070_36'); 
INSERT INTO EXEMPLAIRE VALUES (1109, '30-05-2016',17,'EMPRUNTABLE','BON','9_782070_36'); 


prompt ------------------------------------------;
prompt -----     insertion EMPRUNT   ------------;
prompt ------------------------------------------;


INSERT INTO EMPRUNT VALUES (911023,5003,'10-03-2020', '30-03-2020','30-03-2020',NULL); 
INSERT INTO EMPRUNT VALUES (911023,5005,'30-03-2020','15-04-2020','10-04-2020',NULL); 
INSERT INTO EMPRUNT VALUES (911023,1012,'30-03-2020', '15-04-2020','10-04-2020',NULL); 
INSERT INTO EMPRUNT VALUES (911023,5103,'17-06-2020', '30-06-2020','20-07-2020',1); 
INSERT INTO EMPRUNT VALUES (901001,4203,'03-01-2019', '18-01-2019','18-01-2019',NULL); 
INSERT INTO EMPRUNT VALUES (901001,5005,'03-01-2019', '18-01-2019','18-01-2019',NULL); 
INSERT INTO EMPRUNT VALUES (911007,4203,'25-02-2019', '08-03-2019','25-03-2019',1); 
INSERT INTO EMPRUNT VALUES (911007,1010,'13-05-2019', '31-05-2019','31-05-2019',NULL); 
INSERT INTO EMPRUNT VALUES (921102,4204,'08-08-2020', '22-08-2020','30-08-2020',NULL); 
INSERT INTO EMPRUNT VALUES (921102,5005,'08-08-2020', '22-08-2020','30-08-2020',NULL); 
INSERT INTO EMPRUNT VALUES (911021,5004,'10-12-2020', '30-12-2020','28-12-2020',NULL); 
INSERT INTO EMPRUNT VALUES (911007,5004,'20-07-2020', '10-08-2020','10-08-2020',NULL); 
INSERT INTO EMPRUNT VALUES (911007,4204,'19-01-2021', '10-02-2021', NULL, 1); 
INSERT INTO EMPRUNT VALUES (911007,2673,'10-12-2020', '30-12-2020','28-12-2020', NULL); 
INSERT INTO EMPRUNT VALUES (902075,2673,'15-02-2021', '28-02-2021', NULL, NULL); 
INSERT INTO EMPRUNT VALUES (902075,1010,'05-01-2021', '25-01-2021', NULL, 1); 
INSERT INTO EMPRUNT VALUES (921102,6006,'20-12-2020', '10-01-2021', NULL, 2); 
INSERT INTO EMPRUNT VALUES (911023,6007,'22-12-2020', '12-01-2021','13-01-2021',NULL); 
INSERT INTO EMPRUNT VALUES (902043,7001,'15-09-2018', '09-10-2018','10-10-2018', NULL); 
INSERT INTO EMPRUNT VALUES (902043,3014,'01-10-2018', '21-10-2018','20-11-2018', 2); 
INSERT INTO EMPRUNT VALUES (902043,3014,'01-12-2018', '20-12-2018','20-12-2018', NULL); 
INSERT INTO EMPRUNT VALUES (911023,1109,'15-09-2020', '05-10-2020','05-11-2020', 2); 
INSERT INTO EMPRUNT VALUES (902043,7001,'20-11-2018', '10-12-2018','10-12-2018', NULL); 
INSERT INTO EMPRUNT VALUES (901001,7001,'30-01-2018', '20-02-2018','18-02-2018', NULL); 
INSERT INTO EMPRUNT VALUES (901001,7001,'22-05-2020', '12-06-2020','15-06-2020', NULL); 
INSERT INTO EMPRUNT VALUES (901001,5003,'10-03-2020', '30-03-2020','30-03-2020',NULL); 
INSERT INTO EMPRUNT VALUES (902043,5003,'10-03-2020', '30-03-2020','30-03-2020',NULL); 
INSERT INTO EMPRUNT VALUES (902075,5003,'10-03-2020', '30-03-2020','30-03-2020',NULL); 
INSERT INTO EMPRUNT VALUES (911007,5003,'10-03-2020', '30-03-2020','30-03-2020',NULL); 
INSERT INTO EMPRUNT VALUES (911021,5003,'10-03-2020', '30-03-2020','30-03-2020',NULL); 
INSERT INTO EMPRUNT VALUES (911022,5003,'10-03-2020', '30-03-2020','30-03-2020',NULL);   
INSERT INTO EMPRUNT VALUES (922016,5003,'10-03-2020', '30-03-2020','30-03-2020',NULL);  
INSERT INTO EMPRUNT VALUES (921102,5003,'10-03-2020', '30-03-2020','30-03-2020',NULL);  
INSERT INTO EMPRUNT VALUES (922143,5003,'10-03-2020', '30-03-2020','30-03-2020',NULL); 
INSERT INTO EMPRUNT VALUES (932010,5003,'10-03-2020', '30-03-2020','30-03-2020',NULL); 
