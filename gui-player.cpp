// Anne Warden
// CS375 Final Project
// gui-player.cpp

#include <gtk/gtk.h>

using namespace std;

void callback( GtkWidget *widget,
	       gpointer   data)
{
  g_print("You have selected %s\n", (gchar *)data);
}

gint delete_event( GtkWidget *widget,
		   GdkEvent  *event,
		   gpointer   data )
{
  gtk_main_quit ();
  return FALSE;
}

int main(int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *box1, *vbox;
  
  // Create Containers
  gtk_init(&argc, &argv);
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Rock, Paper, Scissors!");
  g_signal_connect(G_OBJECT (window), "delete_event",
		   G_CALLBACK (delete_event), NULL);
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);
  vbox = gtk_vbox_new (TRUE, 0);
  gtk_container_add (GTK_CONTAINER (window), vbox);
  box1 = gtk_hbox_new (TRUE, 10);
  
  // Define Buttons
  button = gtk_button_new_with_label ("Rock");
  g_signal_connect (G_OBJECT (button), "clicked",
		    G_CALLBACK (callback), (gpointer) "Rock");
  gtk_box_pack_start(GTK_BOX(box1), button, TRUE, TRUE, 0);
  gtk_widget_show(button);
  button = gtk_button_new_with_label ("Paper");
  g_signal_connect (G_OBJECT (button), "clicked",
		    G_CALLBACK (callback), (gpointer) "Paper");
  gtk_box_pack_start(GTK_BOX (box1), button, TRUE, TRUE, 0);
  gtk_widget_show (button);
  button = gtk_button_new_with_label ("Scissors");
  g_signal_connect (G_OBJECT (button), "clicked",
		    G_CALLBACK (callback), (gpointer) "Scissors");
  gtk_box_pack_start(GTK_BOX (box1), button, TRUE, TRUE, 0);
  gtk_widget_show (button);
  gtk_box_pack_start(GTK_BOX (vbox), box1, TRUE, TRUE, 0);
  
  // Show Boxes
  gtk_widget_show (box1);
  gtk_widget_show (vbox);
  gtk_widget_show (window);
  
  gtk_main();
  return 0;
}
