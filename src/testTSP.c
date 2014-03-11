#include <gtk/gtk.h>
#include <matrice.h>
#include <graphe.h>
#include <stdlib.h>
#include <stdio.h>
#include <heuristique.h>

static Matrice m;

static void buttonChargerMatrice( GtkWidget *widget,gpointer   data ){
  //m = chargerMatrice("res/exemple10.tsp");
  GtkWidget *p_dialog = NULL;

  p_dialog = gtk_file_chooser_dialog_new ("Charger une Matrice", NULL,
                                          GTK_FILE_CHOOSER_ACTION_OPEN,
                                          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                          NULL);
  FileFilter filtre;
  if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT){
    gchar *file_name = NULL;

    file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
    m = chargerMatrice(file_name);
    g_free (file_name), file_name = NULL;
  }

  gtk_widget_destroy (p_dialog);
}

static void buttonAfficherMatrice( GtkWidget *widget,gpointer   data ){
  afficherMatriceInt(m);
}

static void buttonHeuristiqueMatrice( GtkWidget *widget,gpointer   data ){
  heuristiqueMatrice(m);
}

static gboolean delete_event( GtkWidget *widget,GdkEvent  *event,gpointer   data ){
  deleteMatrice(m);
  gtk_main_quit();
  return TRUE;
}

static void destroy( GtkWidget *widget,gpointer   data ){
    gtk_main_quit ();
}

int main( int   argc,char *argv[] ){

    GtkWidget *window;
    GtkWidget *button[3];
    GtkWidget *box;

    gtk_init (&argc, &argv);
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
    g_signal_connect(window, "delete-event",G_CALLBACK(delete_event), NULL);
    
    g_signal_connect(window, "destroy",G_CALLBACK(destroy), NULL);
    
    //gtk_container_set_border_width(GTK_CONTAINER (window), 10);
    
    box = gtk_vbox_new(TRUE,0);
    gtk_container_add(GTK_CONTAINER (window),box);

    button[0] = gtk_button_new_with_label("Charger Matrice");
    button[1] = gtk_button_new_with_label("Afficher la Matrice");
    button[2] = gtk_button_new_with_label("Calculer heuristique");

    gtk_box_pack_start(GTK_BOX(box), button[0], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), button[1], FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), button[2], FALSE, FALSE, 0);

    gtk_widget_show_all(window);
    
    g_signal_connect(button[0], "clicked",G_CALLBACK(buttonChargerMatrice), NULL);
    g_signal_connect(button[1], "clicked",G_CALLBACK(buttonAfficherMatrice), NULL);
    g_signal_connect(button[2], "clicked",G_CALLBACK(buttonHeuristiqueMatrice), NULL);

    gtk_main ();
    
    return 0;
}
