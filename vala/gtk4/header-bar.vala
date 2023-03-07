const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk4.HeaderBar";
const string appTitle = "<span weight='bold'>GtkHeaderBar</span>";
const string appSubtitle = "A (client-side) window decoration widget";

int main(string[] args) {
  var app = new Gtk.Application(appID, ApplicationFlags.FLAGS_NONE);
  app.startup.connect(onStartup);
  app.activate.connect(onActivate);

  return app.run(args);
}

void onActivate(Application self) {
  var window = (self as Gtk.Application)?.get_active_window();
  window?.present();
}

void onStartup(Application self) {
  var window = new Gtk.ApplicationWindow(self as Gtk.Application);
  var titleLabel = new Gtk.Label(appTitle);
  var subtitleLabel = new Gtk.Label(appSubtitle);
  var titleBox = new Gtk.Box(Gtk.Orientation.VERTICAL, 0);
  var header = new Gtk.HeaderBar();

  titleLabel.use_markup = true;

  titleBox.margin_top = 4;
  titleBox.margin_bottom = 4;
  titleBox.valign = Gtk.Align.CENTER;
  titleBox.append(titleLabel);
  titleBox.append(subtitleLabel);

  header.title_widget = titleBox;
  header.show_title_buttons = true;

  window.titlebar = header;
  window.set_default_size(400, 400);
}