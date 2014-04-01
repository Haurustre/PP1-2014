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
    //--------Matrice -------------------------------
    titre[0] = gtk_label_new("Matrice");
    buttonMatrice[0] = gtk_button_new_with_label("Charger Matrice");
    buttonMatrice[1] = gtk_button_new_with_label("Afficher la Matrice (entiers)");
    buttonMatrice[2] = gtk_button_new_with_label("Afficher la Matrice");
    buttonMatrice[3] = gtk_button_new_with_label("Calculer heuristique");


    gtk_table_attach_defaults(GTK_TABLE(table),titre[0], 0,150,0,50);
    gtk_table_attach_defaults(GTK_TABLE(table),buttonMatrice[0], 0,150,50,100);
    gtk_table_attach_defaults(GTK_TABLE(table),buttonMatrice[1], 0,150,110,160);
    gtk_table_attach_defaults(GTK_TABLE(table),buttonMatrice[2], 0,150,160,210);
    gtk_table_attach_defaults(GTK_TABLE(table),buttonMatrice[3], 0,150,220,270);
    //-------Graphe------------------------------------
    titre[1] = gtk_label_new("Graphe");
    buttonGraphe[0] = gtk_button_new_with_label("Charger Graphe");
    buttonGraphe[1] = gtk_button_new_with_label("Afficher le Graphe");
    buttonGraphe[2] = gtk_button_new_with_label("Calculer MST");

    gtk_table_attach_defaults(GTK_TABLE(table), titre[1],150,300,0,50);
    gtk_table_attach_defaults(GTK_TABLE(table), buttonGraphe[0],150,300,50,100);
    gtk_table_attach_defaults(GTK_TABLE(table), buttonGraphe[1],150,300,110,160);
    gtk_table_attach_defaults(GTK_TABLE(table), buttonGraphe[2],150,300,220,270);

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
