#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>


#define buff_size 100


typedef struct{
  char *char_buffer;
  int count;
}Data;


static void edit_charbuff (GtkWidget *button, gpointer user_data){
  Data *data_ = (Data*)user_data;
  const char* string_ = gtk_button_get_label(GTK_BUTTON(button));
  int j = data_->count;
  data_->char_buffer[j] = string_[0];
  printf("charbuffer=%c\n", data_->char_buffer[0]);
  
  data_->count+=1;

  printf("count=%d\n",j);
}

void cleanup_data(GtkWidget *widget, gpointer user_data){
  Data *data_ = (Data*)user_data;
  free(data_->char_buffer);
  free(data_);

}



static void activate (GtkApplication *app, gpointer user_data){
	GtkWidget *window= NULL;
	GtkWidget *grid= NULL;
  GtkWidget *entry= NULL;


	window = gtk_application_window_new(app);
	gtk_window_set_title (GTK_WINDOW (window), "Window");
	gtk_window_set_default_size (GTK_WINDOW (window), 800, 800);
  gtk_window_present (GTK_WINDOW (window));
	
	grid = gtk_grid_new ();
	
  gtk_window_set_child (GTK_WINDOW (window), grid);
	gtk_grid_set_row_spacing(GTK_GRID(grid), 5);   
	gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

  


  GtkWidget *widget_array[10];

	widget_array[0] = gtk_button_new_with_label("0");
	g_signal_connect (widget_array[0], "clicked", NULL, NULL);
	gtk_grid_attach(GTK_GRID(grid), widget_array[0] ,0 , 0 , 10 , 10 ); 
	

 // typedef struct{
   // GtkEntryBuffer *p_buffer; 
    //int *p_No;  
  //}EntryData;
  // U ARE MALLOCING EACH ITERATION WHICH IS COMPLETTLY WRONG , U NEED A ARRAY AT BEST FOR EACH BUTTONS DATA TO BE SENT


  Data *data_ = (Data*)malloc(sizeof(Data)*1);

  data_->char_buffer = (char*)malloc(sizeof(char)*100);
  data_->count=0; 

  for (int i = 1 ; i <  10 ; i++){
    char str[2];
		str[0] = i+'0';
    str[1] = '\0' ;
		widget_array[i] = gtk_button_new_with_label(&(str[0]));

    
    g_signal_connect (widget_array[i], "clicked", G_CALLBACK (edit_charbuff),data_ );
		gtk_grid_attach_next_to(GTK_GRID(grid), widget_array[i], widget_array[i-1], GTK_POS_RIGHT , 10 , 10 );
	}	


	gtk_window_present (GTK_WINDOW (window));
  g_signal_connect(window, "destroy", G_CALLBACK(cleanup_data), data_);
}



int main(int argc , char **argv){
	GtkApplication *app;
	int status;
	
  
	app = gtk_application_new ("org.sanjith.calculator", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);
	
		
	return status;
}
