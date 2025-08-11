const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.Expander";
const string appTitle = "Gtk.Expander";
const string expanderTitle = "  <span size='large' font_weight='bold'>Lorem ipsum</span>  ";
const string expanderText = """Duis in metus eros. Duis faucibus rutrum eros eu
vestibulum. Proin et arcu nulla. Etiam at lacinia nibh. Vivamus pellentesque
nunc nibh, ac dignissim massa lobortis ut. Integer eu felis in elit semper
ullamcorper at in ipsum. Suspendisse tempus massa vel nibh tristique vestibulum.
Vestibulum varius eu nunc eu interdum. Curabitur pulvinar velit in purus
facilisis, et auctor augue consequat. Donec finibus felis ligula, a convallis
justo tristique a.""";

int main(string[] args) {
  var app = new Gtk.Application(appID, 0);
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
  var expander = new Gtk.Expander(expanderTitle);
  var expanderLabel = new Gtk.Label(expanderText);

  window.add(expander);
  window.title = appTitle;
  window.resizable = false;
  window.border_width = 10;

  expander.add(expanderLabel);
  expander.show_all();
  expander.use_markup = true;
}