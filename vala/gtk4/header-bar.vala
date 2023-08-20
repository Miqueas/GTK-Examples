const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk4.HeaderBar";
const string appTitle = "<span weight='bold'>GtkHeaderBar</span>";
const string appSubtitle = "<span weight='light'>App subtitle</span>";

int main(string[] args) {
  var app = new Gtk.Application(appID, ApplicationFlags.FLAGS_NONE);
  app.startup.connect(onAppStartup);
  app.activate.connect(onAppActivate);

  return app.run(args);
}

void onAppActivate(Application self) {
  var window = (self as Gtk.Application)?.get_active_window();
  window?.present();
}

void onAppStartup(Application self) {
  var window = new Gtk.ApplicationWindow(self as Gtk.Application);
  var titleLabel = new Gtk.Label(appTitle);
  var subtitleLabel = new Gtk.Label(appSubtitle);
  var titleBox = new Gtk.Box(Gtk.Orientation.VERTICAL, 4);
  var header = new Gtk.HeaderBar();

  window.titlebar = header;
  window.set_default_size(400, 400);

  titleLabel.use_markup = true;
  subtitleLabel.use_markup = true;

  titleBox.margin_top = 4;
  titleBox.margin_bottom = 4;
  titleBox.valign = Gtk.Align.CENTER;
  titleBox.append(titleLabel);
  titleBox.append(subtitleLabel);

  header.title_widget = titleBox;
  header.show_title_buttons = true;
}