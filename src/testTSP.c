#include <gtk/gtk.h>
#include <matrice.h>
#include <graphe.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <heuristique.h>
#include <mst.h>

static Matrice m;
static Graphe g;
//char affiche[2048];

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

static void buttonAfficherMatriceInt( GtkWidget *widget,gpointer   data ){
  if(m == NULL)
    printf("Erreur: Aucune matrice chargee\n");
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
    heuristiqueMatrice(m);
  }
}

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
    calculerMST(g);

  }
}

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

int main( int   argc,char *argv[] ){
  /* g = chargerGraphe("res/exemple10.tsp");
  m = chargerMatrice("res/exemple10.tsp");

  calculerMST(g);
  heuristiqueMatrice(m);

  deleteGraphe(g);
  deleteMatrice(m);*/


    GtkWidget *window;
    GtkWidget *buttonChargerTSP;
    GtkWidget *buttonMatrice[3];
    GtkWidget *buttonGraphe[2];
    GtkWidget *table;
    GtkWidget *titre[2];
    gtk_init (&argc, &argv);    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);   
    g_signal_connect(window, "delete-event",G_CALLBACK(delete_event), NULL);
    g_signal_connect(window, "destroy",G_CALLBACK(destroy), NULL);
    
    //---box-------------------------------------
    table = gtk_table_new(150,150,TRUE);
    gtk_container_set_border_width(GTK_CONTAINER(window),10); 
    gtk_container_add(GTK_CONTAINER (window),table);

    buttonChargerTSP = gtk_button_new_with_label("Charger Matrice et Graphe");
    gtk_table_attach_defaults(GTK_TABLE(table), buttonChargerTSP,0,200,0,50);
    //--------Matrice -------------------------------
    titre[0] = gtk_label_new("Matrice");
    buttonMatrice[0] = gtk_button_new_with_label("Afficher la Matrice (Fenetre)");
    buttonMatrice[1] = gtk_button_new_with_label("Afficher la Matrice (Terminal)");
    buttonMatrice[2] = gtk_button_new_with_label("Calculer heuristique");


    gtk_table_attach_defaults(GTK_TABLE(table),titre[0], 0,100,50,100);

    gtk_table_attach_defaults(GTK_TABLE(table),buttonMatrice[0], 0,100,110,160);
    gtk_table_attach_defaults(GTK_TABLE(table),buttonMatrice[1], 0,100,160,210);
    gtk_table_attach_defaults(GTK_TABLE(table),buttonMatrice[2], 0,100,220,270);
    //-------Graphe------------------------------------
    titre[1] = gtk_label_new("Graphe");
    buttonGraphe[0] = gtk_button_new_with_label("Afficher le Graphe");
    buttonGraphe[1] = gtk_button_new_with_label("Calculer MST");

    gtk_table_attach_defaults(GTK_TABLE(table), titre[1],100,200,50,100);
    gtk_table_attach_defaults(GTK_TABLE(table), buttonGraphe[0],100,200,110,160);
    gtk_table_attach_defaults(GTK_TABLE(table), buttonGraphe[1],100,200,220,270);

    //-------Connection des actions-----------------------------------
    gtk_widget_show_all(window);
    
    g_signal_connect(buttonMatrice[0], "clicked",G_CALLBACK(buttonAfficherMatriceInt), NULL);
    g_signal_connect(buttonMatrice[1], "clicked",G_CALLBACK(buttonAfficherMatrice), NULL);
    g_signal_connect(buttonMatrice[2], "clicked",G_CALLBACK(buttonHeuristiqueMatrice), NULL);
    g_signal_connect(buttonGraphe[0], "clicked",G_CALLBACK(buttonAfficherGraphe), NULL);
    g_signal_connect(buttonGraphe[1], "clicked",G_CALLBACK(buttonCalculerMST), NULL);
    g_signal_connect(buttonChargerTSP, "clicked",G_CALLBACK(buttonCharger), NULL);
    gtk_main ();

    
    return 0;
}
