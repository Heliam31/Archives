prompt "Suppression des relations"
BEGIN
EXECUTE IMMEDIATE 'DROP TABLE AB_NB';
EXCEPTION
 WHEN OTHERS THEN
	IF SQLCODE != -942 THEN
	RAISE;
	END IF;
END;
/

CREATE TABLE AB_NB
(
	NUMERO NUMERIC(6) PRIMARY KEY,
	NB NUMERIC(3)
);


/*---------------------------FONC prets-----------------------------*/
CREATE OR REPLACE FUNCTION nb_prets (num_abo IN EMPRUNT.NUM_AB%TYPE)
RETURN INTEGER IS
	nb_empr INTEGER;
BEGIN
	SELECT COUNT(*) INTO nb_empr 
	FROM EMPRUNT WHERE NUM_AB=num_abo;
	RETURN(nb_empr);
END;
/

SELECT NUM_AB, nb_prets(NUM_AB) FROM DUAL, EMPRUNT E WHERE E.NUM_AB=NUM_AB GROUP BY NUM_AB; 

/*----------------------------BEGIN PL/SQL--------------------------*/
DECLARE
	num_abo AB_NB.NUMERO%TYPE;
	nb_empr AB_NB.NB%TYPE;
	cpt INTEGER;
	abo_null_exception EXCEPTION;
	empr_null_exception EXCEPTION;

BEGIN
	num_abo := &num_abo;
	
	SELECT COUNT(*) INTO cpt FROM ABONNE WHERE NUM_AB = num_abo;

	IF cpt = 0 THEN RAISE abo_null_exception; 
	END IF;

	nb_empr := nb_prets(num_abo);

	IF nb_empr = 0 THEN RAISE empr_null_exception;

	else INSERT INTO AB_NB VALUES (num_abo, nb_empr);
	END IF;

EXCEPTION
	WHEN abo_null_exception THEN INSERT INTO AB_NB VALUES (num_abo, -1);
	
	WHEN empr_null_exception THEN INSERT INTO AB_NB(NUMERO, NB) VALUES (num_abo, NULL);
END;
/