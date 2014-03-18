#include <gtk/gtk.h>
#include <matrice.h>
#include <graphe.h>
#include <stdlib.h>
#include <stdio.h>
#include <heuristique.h>
#include <mst.h>

static Matrice m;
static Graphe g;

static void buttonChargerMatrice( GtkWidget *widget,gpointer   data ){
  GtkWidget *p_dialog = NULL;

  p_dialog = gtk_file_chooser_dialog_new ("Charger une Matrice", NULL,
                                          GTK_FILE_CHOOSER_ACTION_OPEN,
                                          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                          NULL);

  if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT){
    gchar *file_name = NULL;

    file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
    m = chargerMatrice(file_name);
    g_free (file_name), file_name = NULL;
  }

  gtk_widget_destroy (p_dialog);
}

static void buttonAfficherMatriceInt( GtkWidget *widget,gpointer   data ){
  if(m == NULL)
    printf("Erreur: Aucune matrice chargee\n");
  else
    afficherMatriceInt(m);
}
static void buttonAfficherMatrice( GtkWidget *widget,gpointer   data ){
  if(m == NULL)
    printf("Erreur: Aucune matrice chargee\n");
  else
    afficherMatrice(m);
}
static void buttonHeuristiqueMatrice( GtkWidget *widget,gpointer   data ){
  if(m == NULL)
    printf("Erreur: Aucune matrice chargee\n");
  else
    heuristiqueMatrice(m);
}

static void buttonChargerGraphe( GtkWidget *widget,gpointer   data ){
  GtkWidget *p_dialog = NULL;

  p_dialog = gtk_file_chooser_dialog_new ("Charger un Graphe", NULL,
                                          GTK_FILE_CHOOSER_ACTION_OPEN,
                                          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                          NULL);

  if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT){
    gchar *file_name = NULL;

    file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
    g = chargerGraphe(file_name);
    g_free (file_name), file_name = NULL;
  }

  gtk_widget_destroy (p_dialog);
}
static void buttonAfficherGraphe( GtkWidget *widget,gpointer   data ){
  if(g == NULL)
    printf("Erreur: Aucun graphe charge\n");
  else
    afficherGraphe(g);
}
static void buttonCalculerMST( GtkWidget *widget,gpointer   data ){
  if(g == NULL)
    printf("Erreur: Aucun graphe charge\n");
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

    GtkWidget *window;
    GtkWidget *buttonMatrice[4];
    GtkWidget *buttonGraphe[3];
    GtkWidget *box;

    gtk_init (&argc, &argv);    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);   
    g_signal_connect(window, "delete-event",G_CALLBACK(delete_event), NULL);
    g_signal_connect(window, "destroy",G_CALLBACK(destroy), NULL);
    
    //---box-------------------------------------
    box = gtk_vbox_new(TRUE,0);
    gtk_container_add(GTK_CONTAINER (window),box);
    //--------Matrice -------------------------------
    buttonMatrice[0] = gtk_button_new_with_label("Charger Matrice");
    buttonMatrice[1] = gtk_button_new_with_label("Afficher la Matrice (entiers)");
    buttonMatrice[2] = gtk_button_new_with_label("Afficher la Matrice");
    buttonMatrice[3] = gtk_button_new_with_label("Calculer heuristique");

    gtk_box_pack_start(GTK_BOX(box), buttonMatrice[0], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), buttonMatrice[1], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), buttonMatrice[2], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), buttonMatrice[3], FALSE, FALSE, 0);
    
    //-------Graphe------------------------------------

    buttonGraphe[0] = gtk_button_new_with_label("Charger Graphe");
    buttonGraphe[1] = gtk_button_new_with_label("Afficher le Graphe");
    buttonGraphe[2] = gtk_button_new_with_label("Calculer MST");

    gtk_box_pack_start(GTK_BOX(box), buttonGraphe[0], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), buttonGraphe[1], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), buttonGraphe[2], FALSE, FALSE, 0);
    //-------Connection des actions-----------------------------------
    gtk_widget_show_all(window);
    
    g_signal_connect(buttonMatrice[0], "clicked",G_CALLBACK(buttonChargerMatrice), NULL);
    g_signal_connect(buttonMatrice[1], "clicked",G_CALLBACK(buttonAfficherMatriceInt), NULL);
    g_signal_connect(buttonMatrice[2], "clicked",G_CALLBACK(buttonAfficherMatrice), NULL);
    g_signal_connect(buttonMatrice[3], "clicked",G_CALLBACK(buttonHeuristiqueMatrice), NULL);
g_signal_connect(buttonGraphe[0], "clicked",G_CALLBACK(buttonChargerGraphe), NULL);
    g_signal_connect(buttonGraphe[1], "clicked",G_CALLBACK(buttonAfficherGraphe), NULL);
    g_signal_connect(buttonGraphe[2], "clicked",G_CALLBACK(buttonCalculerMST), NULL);

    gtk_main ();
    
    return 0;
}
