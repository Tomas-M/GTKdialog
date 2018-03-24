#include <stdlib.h>
#include <gtk/gtk.h>

static gchar *option_title = NULL;
static gchar *option_message = NULL;
static gchar *option_yes = NULL;
static gchar *option_no = NULL;

static const GOptionEntry option_entries[] = {
	{ "title", 't', 0, G_OPTION_ARG_STRING, &option_title, "Dialog title", "title" },
	{ "message", 'm', 0, G_OPTION_ARG_STRING, &option_message, "Dialog message", "message" },
	{ "yes", 'y', 0, G_OPTION_ARG_STRING, &option_yes, "Text to display on Yes button", "Yes" },
	{ "no", 'n', 0, G_OPTION_ARG_STRING, &option_no, "Text to display on No button", "No" },
	{ NULL }
};

void YesFunc(){ exit(0); }
void NoFunc(){ exit(1); }

int main(int argc, char *argv[])
{
	GOptionContext *context;
	GError *error = NULL;
	gtk_init(&argc, &argv);

	context = g_option_context_new(NULL);
	g_option_context_add_main_entries(context, option_entries, NULL);
	if (!g_option_context_parse(context, &argc, &argv, &error)) {
		g_printerr("ERROR when parsing options: %s\n", error->message);
		exit(2);
	}

	if (!option_title || !option_message || !option_yes) {
		g_print("%s", g_option_context_get_help(context, TRUE, NULL));
		exit(2);
	}

	GtkWidget *label;
	GtkWidget *button;
	GtkWidget *dialog_window;

	dialog_window = gtk_dialog_new ();
	gtk_window_set_title (GTK_WINDOW (dialog_window), option_title);
	gtk_container_border_width (GTK_CONTAINER (dialog_window), 15);

	label = gtk_label_new (option_message);
	gtk_misc_set_padding (GTK_MISC (label), 10, 10);
	gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog_window)->vbox), label, TRUE, TRUE, 0);
	gtk_widget_show (label);

	button = gtk_button_new_with_label (option_yes);
	gtk_signal_connect (GTK_OBJECT (button), "clicked", GTK_SIGNAL_FUNC (YesFunc), dialog_window);
	gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog_window)->action_area), button, TRUE, TRUE, 0);
	gtk_widget_show (button);

	if (option_no)
	{
		button = gtk_button_new_with_label (option_no);
		gtk_signal_connect (GTK_OBJECT (button), "clicked", GTK_SIGNAL_FUNC (NoFunc), dialog_window);
			GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
			gtk_box_pack_start (GTK_BOX (GTK_DIALOG (dialog_window)->action_area), button, TRUE, TRUE, 0);
			gtk_widget_grab_default (button);
			gtk_widget_show (button);
	}

	gtk_widget_show (dialog_window);

	g_signal_connect(G_OBJECT(dialog_window), "destroy", NoFunc, NULL);
	g_signal_connect(G_OBJECT(dialog_window), "delete-event", NoFunc, NULL);
	gtk_main();
	return 0;
}
