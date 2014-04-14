/**
 * \file testTSP.c
 * \brief Programmede test
 * \author Ghislain Hudry
 * \version 0.1
 * \date 14 Fevrier 2014
 *
 * Programme avec interface graphique testant les algorithmes.
 *
 */
#include <gtk/gtk.h>
#include <matrice.h>
#include <graphe.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <heuristique.h>
#include <mst.h>
#include <brutForce.h>
#include <branchandbound.h>

static Matrice m;
static Graphe g;

GtkWidget *window;
GtkWidget *buttonChargerTSP;
GtkWidget *buttonChoix;
GtkWidget *label_choix;
GtkWidget *buttonMatrice[3];
GtkWidget *buttonGraphe[4];
GtkWidget *table;
GtkWidget *titre[2];
//char affiche[2048];
int choix = -1;

/**
 * \fn static void afficherMessage(char * msg,gpointer data)
 * \brief Affiche simplement un message d'information
 *
 * \return void
 */
static void afficherMessage(char * msg,gpointer data){
  GtkWidget *p_information = gtk_message_dialog_new (GTK_WINDOW(data),
						       GTK_DIALOG_MODAL,
						       GTK_MESSAGE_INFO,
						       GTK_BUTTONS_OK,
						       "%s",msg);
    gtk_window_set_resizable (GTK_WINDOW(p_information), TRUE);
    gtk_dialog_run(GTK_DIALOG(p_information));
    gtk_widget_destroy(p_information);
}

/**
 * \fn static void buttonChoixVille(GtkWidget * widget,gpointer data)
 * \brief Permet de choisir une ville de départ pour lancer ensuite les algorithmes
 *
 * \return void
 */
static void buttonChoixVille(GtkWidget * widget,gpointer data){
  if(m != NULL){
  GtkWidget* pBoite;
  GtkWidget* pEntry;
 
  /* Création de la boite de dialogue */
  /* 1 bouton Valider */
  /* 1 bouton Annuler */
  pBoite = gtk_dialog_new_with_buttons("Choisir la ville de depart",
				       GTK_WINDOW(window),
				       GTK_DIALOG_MODAL,
				       GTK_STOCK_OK,GTK_RESPONSE_OK,
				       GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
				       NULL);
 
  /* Création de la zone de saisie */
  pEntry = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(pEntry), "Numero ville");
  /* Insertion de la zone de saisie dans la boite de dialogue */
  /* Rappel : paramètre 1 de gtk_box_pack_start de type GtkBox */
  gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox), pEntry, TRUE, FALSE, 0);
 
  /* Affichage des éléments de la boite de dialogue */
  gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);
 
  /* On lance la boite de dialogue et on récupéré la réponse */
  switch (gtk_dialog_run(GTK_DIALOG(pBoite)))
    {
      /* L utilisateur valide */
    case GTK_RESPONSE_OK:
      choix = atoi(gtk_entry_get_text(GTK_ENTRY(pEntry)));
      gtk_label_set_text(GTK_LABEL(label_choix),gtk_entry_get_text(GTK_ENTRY(pEntry)));
      break;
      /* L utilisateur annule */
    case GTK_RESPONSE_CANCEL:
      break;
    case GTK_RESPONSE_NONE:
      break;
    default: break;
    }
  if(choix < 0 || choix > getLargeurMatrice(m)-1)
    choix = -1;
  /* Destruction de la boite de dialogue */
  gtk_widget_destroy(pBoite);
  }
  else{
    afficherMessage("Erreur: chargez un fichier tsp avant de choisir la ville de depart",data);
  }
}

static void buttonAfficherMatriceInt( GtkWidget *widget,gpointer   data ){
  if(m == NULL)
    afficherMessage("Erreur: Aucune matrice chargee",data);
  else{
    char affiche[2048];
    if(getLargeurMatrice(m) < 15){
    afficherMatriceInt(m,affiche);
    }
    else
      sprintf(affiche,"Matrice trop grande pour etre affiche dans une fenetre");
    afficherMessage(affiche,data);
  }
}
static void buttonAfficherMatrice( GtkWidget *widget,gpointer   data ){
  if(m == NULL)
    afficherMessage("Erreur: Aucune matrice chargee",data);
  else
    afficherMatrice(m);
}
static void buttonHeuristiqueMatrice( GtkWidget *widget,gpointer   data ){
  if(m == NULL)
    afficherMessage("Erreur: Aucune matrice chargee",data);
  else{
    if(choix == -1){
      afficherMessage("Aucune ville de depart sélectionnée\nCalcule du chemin optimal",data);
      heuristiqueMatrice(m);
    }
    else
      heuristiqueVille(m,choix);
  }
}

/**
 * \fn static void buttonCharger( GtkWidget *widget,gpointer   data )
 * \brief charge les deux structures Graphe et Matrice à partir d'un explorateur de fichier simple
 *
 * \return void
 */
static void buttonCharger( GtkWidget *widget,gpointer   data ){
  GtkWidget *p_dialog = NULL;
  GtkWidget *p_information;

  p_dialog = gtk_file_chooser_dialog_new ("Charger un probleme tsp", NULL,
                                          GTK_FILE_CHOOSER_ACTION_OPEN,
                                          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                          NULL);

  if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT){
    gchar *file_name = NULL;

    file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
    g = chargerGraphe(file_name);
    m = chargerMatrice(file_name);

    g_free (file_name), file_name = NULL;
  }
  gtk_widget_destroy (p_dialog);

  if(!matriceSymetrique(m)){
    afficherMessage("Attention ! Matrice asymétrique !",data);
  }
  else if(!matricePlanaire(m)){  
    afficherMessage("Attention ! Matrice non planaire !",data);
  }

}

static void buttonAfficherGraphe( GtkWidget *widget,gpointer   data ){
  if(g == NULL)
    afficherMessage("Erreur: Aucun graphe charge",data);
  else{
    char affiche[2048];
    if(getNombreSommets(g) <= 10){
      afficherGraphe(g,affiche);
    }
    else{
      affiche[0] = '\0';
      strcat(affiche,"Affichage trop long pour etre affiché en fenetre");
      afficherGrapheTerminal(g);
     }
    afficherMessage(affiche,data);
  }
}

static void buttonCalculerMST( GtkWidget *widget,gpointer   data ){
  if(g == NULL)
    afficherMessage("Erreur: Aucun graphe charge",data);
  else{
    if(choix == -1){
      afficherMessage("Aucune ville de depart sélectionnée\nCalcule du parcourt optimal",data);
      calculerMST(g);
    }
    else
      calculerMSTVille(g,choix);

  }
}

static void buttonCalculerBrutForce( GtkWidget *widget,gpointer   data ){
  if(g == NULL)
    afficherMessage("Erreur: Aucun graphe charge",data);
  else{
    if(choix == -1)
      afficherMessage("Aucune ville de depart sélectionnée\n",data);
    else
      brutForce(g,choix);

  }
}

static void buttonCalculerBranchAndBound( GtkWidget *widget,gpointer   data ){
  if(g == NULL)
    afficherMessage("Erreur: Aucun graphe charge",data);
  else{
    if(choix == -1)
      afficherMessage("Aucune ville de depart sélectionnée\n",data);
    else
      branchAndBound(g, choix);

  }

}

/**
 * \fn static gboolean delete_event( GtkWidget *widget,GdkEvent  *event,gpointer   data )
 * \brief Permet de liberer la mémoire lorsque l'on ferme l'interface graĥique
 *
 * \return void
 */
static gboolean delete_event( GtkWidget *widget,GdkEvent  *event,gpointer   data ){
  if(m != NULL)
    deleteMatrice(m);
  if(g!= NULL)
    deleteGraphe(g);
  gtk_main_quit();
  return TRUE;
}

static void destroy( GtkWidget *widget,gpointer   data ){
    gtk_main_quit ();
}

/**
 * \fn int main( int   argc,char *argv[] )
 * \brief Entrée du programme.
 *
 * \return EXIT_SUCCESS - Arrêt normal du programme.
 */
int main( int   argc,char *argv[] ){
  /* g = chargerGraphe("../res/exemple10.tsp");
  branchAndBound(g, 0);
  /*
   m = chargerMatrice("res/exemple10.tsp");

  calculerMST(g);
  heuristiqueMatrice(m);

  deleteGraphe(g);
  deleteMatrice(m);*/

  gtk_init (&argc, &argv);    
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);   
  g_signal_connect(window, "delete-event",G_CALLBACK(delete_event), NULL);
  g_signal_connect(window, "destroy",G_CALLBACK(destroy), NULL);
  
  buttonChoix = gtk_button_new_with_label("Ville de depart :");
  label_choix = gtk_label_new("Aucune");
  //---box-------------------------------------
  table = gtk_table_new(150,100,TRUE);
  gtk_container_set_border_width(GTK_CONTAINER(window),5); 
  gtk_container_add(GTK_CONTAINER (window),table);
  
  buttonChargerTSP = gtk_button_new_with_label("Charger Matrice et Graphe");
  gtk_table_attach_defaults(GTK_TABLE(table), buttonChargerTSP,0,100,0,25);
  gtk_table_attach_defaults(GTK_TABLE(table), buttonChoix,0,50,25,50);
  gtk_table_attach_defaults(GTK_TABLE(table), label_choix,50,100,25,50);
  //--------Matrice -------------------------------
  titre[0] = gtk_label_new("Matrice");
  buttonMatrice[0] = gtk_button_new_with_label("Afficher la Matrice (Fenetre)");
  buttonMatrice[1] = gtk_button_new_with_label("Afficher la Matrice (Terminal)");
  buttonMatrice[2] = gtk_button_new_with_label("Calculer heuristique");
  
  
  gtk_table_attach_defaults(GTK_TABLE(table),titre[0], 0,50,50,75);
  
  gtk_table_attach_defaults(GTK_TABLE(table),buttonMatrice[0], 0,50,75,100);
  gtk_table_attach_defaults(GTK_TABLE(table),buttonMatrice[1], 0,50,100,125);
  gtk_table_attach_defaults(GTK_TABLE(table),buttonMatrice[2], 0,50,125,150);
  //-------Graphe------------------------------------
  titre[1] = gtk_label_new("Graphe");
  buttonGraphe[0] = gtk_button_new_with_label("Afficher le Graphe");
  buttonGraphe[1] = gtk_button_new_with_label("Calculer MST");
  buttonGraphe[2] = gtk_button_new_with_label("Calculer Brut Force");
  buttonGraphe[3] = gtk_button_new_with_label("Calculer Branch & Bound");

  gtk_table_attach_defaults(GTK_TABLE(table), titre[1],50,100,50,75);
  
  gtk_table_attach_defaults(GTK_TABLE(table), buttonGraphe[0],50,100,75,100);
  gtk_table_attach_defaults(GTK_TABLE(table), buttonGraphe[1],50,100,100,125);
  gtk_table_attach_defaults(GTK_TABLE(table), buttonGraphe[2],50,100,125,150);
  gtk_table_attach_defaults(GTK_TABLE(table), buttonGraphe[3],50,100,150,175);
  //-------Connection des actions-----------------------------------
  gtk_widget_show_all(window);
  
  g_signal_connect(buttonMatrice[0], "clicked",G_CALLBACK(buttonAfficherMatriceInt), NULL);
  g_signal_connect(buttonMatrice[1], "clicked",G_CALLBACK(buttonAfficherMatrice), NULL);
  g_signal_connect(buttonMatrice[2], "clicked",G_CALLBACK(buttonHeuristiqueMatrice), NULL);
  g_signal_connect(buttonGraphe[0], "clicked",G_CALLBACK(buttonAfficherGraphe), NULL);
  g_signal_connect(buttonGraphe[1], "clicked",G_CALLBACK(buttonCalculerMST), NULL);
  g_signal_connect(buttonGraphe[2], "clicked",G_CALLBACK(buttonCalculerBrutForce), NULL);
  g_signal_connect(buttonGraphe[3], "clicked",G_CALLBACK(buttonCalculerBranchAndBound), NULL);
  g_signal_connect(buttonChargerTSP, "clicked",G_CALLBACK(buttonCharger), NULL);
  g_signal_connect(buttonChoix, "clicked",G_CALLBACK(buttonChoixVille), NULL);
  gtk_main ();

  
  return 0;
}
