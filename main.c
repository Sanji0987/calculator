#include <stdio.h>
#include <gtk/gtk.h>



#define buff_size 1000


static void print_hello (GtkWidget *widget, gpointer data){
  g_print ("Hello World\n");
  char *datap = (char*) data;
  datap[0] = 'c';
  printf("datap : %c\n", datap[0]);
}


static void activate (GtkApplication *app, gpointer user_data){
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *grid;



	window = gtk_application_window_new(app);
	gtk_window_set_title (GTK_WINDOW (window), "Window");
	gtk_window_set_default_size (GTK_WINDOW (window), 800, 800);
  	gtk_window_present (GTK_WINDOW (window));
	
	grid = gtk_grid_new ();
	
  	gtk_window_set_child (GTK_WINDOW (window), grid);
	gtk_grid_set_row_spacing(GTK_GRID(grid), 1);   
	gtk_grid_set_column_spacing(GTK_GRID(grid), 1);



	GtkWidget *widget_array[10];

	widget_array[0] = gtk_button_new_with_label("0");
	g_signal_connect (widget_array[0], "clicked", G_CALLBACK (print_hello), user_data);
	gtk_grid_attach(GTK_GRID(grid), widget_array[0] ,0 , 0 , 100 , 100 );
	
	char str[1]; // {char , '\0'} 

	for (int i = 1 ; i <  10 ; i++){
		str[0] = i + '0';
		widget_array[i] = gtk_button_new_with_label(&(str[0]));
  		g_signal_connect (widget_array[i], "clicked", G_CALLBACK (print_hello), user_data);
		gtk_grid_attach_next_to(GTK_GRID(grid), widget_array[i], widget_array[i-1], GTK_POS_RIGHT , 100 , 100 );
	}	



	


  	gtk_window_present (GTK_WINDOW (window));

}



int main(int argc , char **argv){
	GtkApplication *app;
	int status;
	
	char *buff= (char*) calloc(sizeof(char), buff_size);

	app = gtk_application_new ("org.sanjith.calculator", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (app, "activate", G_CALLBACK (activate), buff);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);
	
		
	free(buff);
	return status;
}
