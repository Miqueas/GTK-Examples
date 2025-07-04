const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.AppChooserWidget";
const string appTitle = "GtkBox";

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
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);
  var appChooserWidget = new Gtk.AppChooserWidget("image/png");
  var settingsLabel = new Gtk.Label("Settings");
  var showAllToggle = new Gtk.CheckButton.with_label("Show all applications");
  var showDefaultToggle = new Gtk.CheckButton.with_label("Show default");
  var showFallbackToggle = new Gtk.CheckButton.with_label("Show fallback");
  var showOtherToggle = new Gtk.CheckButton.with_label("Show other");
  var showRecommendedToggle = new Gtk.CheckButton.with_label(
    "Show recommended"
  );

  with (window) {
    add(box);
    title = appTitle;
    border_width = 10;
    set_default_size(400, 400);
  }

  with (box) {
    pack_start(appChooserWidget, true, true, 0);
    pack_start(settingsLabel, false, false, 0);
    pack_start(showAllToggle, false, false, 0);
    pack_start(showDefaultToggle, false, false, 0);
    pack_start(showFallbackToggle, false, false, 0);
    pack_start(showOtherToggle, false, false, 0);
    pack_start(showRecommendedToggle, false, false, 0);
    show_all();
  }

  settingsLabel.halign = Gtk.Align.START;

  showAllToggle.active = appChooserWidget.show_all;
  showDefaultToggle.active = appChooserWidget.show_default;
  showFallbackToggle.active = appChooserWidget.show_fallback;
  showOtherToggle.active = appChooserWidget.show_other;
  showRecommendedToggle.active = appChooserWidget.show_recommended;

  showAllToggle.toggled.connect(self => {
    appChooserWidget.show_all = self.active;

    if (self.active) {
      showDefaultToggle.active = false;
      showFallbackToggle.active = false;
      showOtherToggle.active = false;
      showRecommendedToggle.active = false;
    }
  });

  showDefaultToggle.toggled.connect(self => {
    appChooserWidget.show_default = self.active;

    if (showAllToggle.active && self.active) showAllToggle.active = false;
  });

  showFallbackToggle.toggled.connect(self => {
    appChooserWidget.show_fallback = self.active;

    if (showAllToggle.active && self.active) showAllToggle.active = false;
  });

  showOtherToggle.toggled.connect(self => {
    appChooserWidget.show_other = self.active;

    if (showAllToggle.active && self.active) showAllToggle.active = false;
  });

  showRecommendedToggle.toggled.connect(self => {
    appChooserWidget.show_recommended = self.active;

    if (showAllToggle.active && self.active) showAllToggle.active = false;
  });
}