package TP3.JunitMaven;
import org.junit.jupiter.api.Test;

import poste.Colis;
import poste.Lettre;
import poste.Recommandation;
import poste.SacPostal;

import static org.junit.jupiter.api.Assertions.*;



public class AppTest 
{
	private static float tolerancePrix = 0.01f;
	private static float toleranceVolume = 0.0000001f;
	
	//Creation des objets sous test
	Lettre lettre1 = new Lettre("Le pere Noel",
			"famille Kirik, igloo 5, banquise nord",
			"7877", 25, 0.00018f, Recommandation.un, false);
	Lettre lettre2 = new Lettre("Le pere Noel",
			"famille Kouk, igloo 2, banquise nord",
			"5854", 18, 0.00018f, Recommandation.deux, true);
	Colis colis1 = new Colis("Le pere Noel", 
			"famille Kaya, igloo 10, terres ouest",
			"7877", 1024, 0.02f, Recommandation.deux, "train electrique", 200);
	
   @Test
   public void testTostring() {
	   assertEquals(colis1.toString(), "Colis 7877/famille Kaya, igloo 10, terres ouest/2/0.02/200.0","toString Colis 1 NOK" );
	   assertEquals(lettre1.toString(), "Lettre 7877/famille Kirik, igloo 5, banquise nord/1/ordinaire","toString Lettre 1 NOK" );
	   assertEquals(lettre2.toString(), "Lettre 5854/famille Kouk, igloo 2, banquise nord/2/urgence" ,"toString Lettre 2 NOK" );

   }
   @Test
   public void testAffranchissement() {
	   assertEquals(1.0f, lettre1.tarifAffranchissement(), tolerancePrix);
	   assertEquals(2.3f, lettre2.tarifAffranchissement(), tolerancePrix);
	   assertEquals(3.5f, colis1.tarifAffranchissement(), tolerancePrix);
   }
   @Test
   public void testRemboursement() {
	   assertEquals(1.5f, lettre1.tarifRemboursement(), tolerancePrix);
	   assertEquals(15.0f, lettre2.tarifRemboursement(), tolerancePrix);
	   assertEquals(100.0f, colis1.tarifRemboursement(), tolerancePrix);		
   }
   
	// TODO test sur les ColisEXpress
   
   //Test sac postaux
   SacPostal sac1 = new SacPostal();
   @Test
   public void remplissageSac() {
	   sac1.ajoute(lettre1);
		sac1.ajoute(lettre2);
		sac1.ajoute(colis1);
		assertEquals(116.5f, sac1.valeurRemboursement(), tolerancePrix);
   }
   @Test
   public void testVolume() {
	   assertEquals(0.025359999558422715, sac1.getVolume(), toleranceVolume);
   }
		SacPostal sac2 = sac1.extraireV1("7877");
		
	public void testVolume2() {	
		assertEquals(0.02517999955569394f, sac2.getVolume(), toleranceVolume);
   }

}