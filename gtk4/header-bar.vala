const string app_id = "io.github.Miqueas.Vala-GTK-Examples.Gtk4.HeaderBar";

int main(string[] args) {
  var app = new Gtk.Application(app_id, ApplicationFlags.FLAGS_NONE);
  app.startup.connect(startup);
  app.activate.connect(activate);

  return app.run(args);
}

void activate(Application self) {
  var win = (self as Gtk.Application)?.get_active_window();
  win?.present();
}

void startup(Application self) {
  var win = new Gtk.ApplicationWindow(self as Gtk.Application);
  var title_lbl = new Gtk.Label("<span weight='bold'>My app</span>");
  var subtitle_lbl = new Gtk.Label("An awesome app that you'll love");
  var title_box = new Gtk.Box(Gtk.Orientation.VERTICAL, 0);
  var header = new Gtk.HeaderBar();

  win.titlebar = header;
  win.set_default_size(400, 400);

  title_lbl.use_markup = true;

  title_box.margin_top = 4;
  title_box.margin_bottom = 4;
  title_box.valign = Gtk.Align.CENTER;
  title_box.append(title_lbl);
  title_box.append(subtitle_lbl);

  header.title_widget = title_box;
  header.show_title_buttons = true;
}