const string appTitle = "GtkWindow";

void main(string[] args) {
  Gtk.init(ref args);

  var window = new Gtk.Window();
  var headerBar = new Gtk.HeaderBar();

  with (headerBar) {
    visible = true;
    title = appTitle;
    show_close_button = true;
  }

  with (window) {
    set_titlebar(headerBar);
    set_default_size(400, 400);
    destroy.connect(Gtk.main_quit);
    present();
  }

  Gtk.main();
}