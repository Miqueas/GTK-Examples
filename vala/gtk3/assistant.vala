const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.Assistant";
const string appTitle = "Gtk.Assistant";
const string welcomeText = "<span font='Bold 16'>Welcome to the GtkAssistant example</span>";
const string finalText = "System installed successfully!";

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
  var window = new Gtk.Assistant();
  var page1 = new Gtk.Label(welcomeText) { visible = true, use_markup = true };
  var page2 = doPage2(window);
  var page3 = doPage3(window);
  var page4 = new Gtk.Label(finalText) { visible = true };

  (self as Gtk.Application)?.add_window(window);

  window.title = appTitle;
  window.set_default_size(800, 400);
  window.cancel.connect(window.destroy);
  window.close.connect(window.destroy);

  window.append_page(page1);
  window.append_page(page2);
  window.append_page(page3);
  window.append_page(page4);

  window.set_page_title(page1, "Welcome");
  window.set_page_title(page2, "Create account");
  window.set_page_title(page3, "Installing system");
  window.set_page_title(page4, "Summary");

  window.set_page_type(page1, Gtk.AssistantPageType.INTRO);
  window.set_page_type(page2, Gtk.AssistantPageType.CONFIRM);
  window.set_page_type(page3, Gtk.AssistantPageType.PROGRESS);
  window.set_page_type(page4, Gtk.AssistantPageType.SUMMARY);

  window.set_page_complete(page1, true);
}

Gtk.Grid doPage2(Gtk.Assistant assistant) {
  var grid = new Gtk.Grid();
  var infoLabel = new Gtk.Label("Fill this form");
  var nameLabel = new Gtk.Label("Full name");
  var usernameLabel = new Gtk.Label("Username");
  var passwordLabel = new Gtk.Label("Password");
  var nameEntry = new Gtk.Entry();
  var usernameEntry = new Gtk.Entry();
  var passwordEntry = new Gtk.Entry();
  var doneButton = new Gtk.Button.with_label("Done");

  grid.column_spacing = 10;
  grid.row_spacing = 10;
  grid.halign = Gtk.Align.CENTER;
  grid.valign = Gtk.Align.CENTER;
  grid.attach(infoLabel, 0, 0, 2, 1);
  grid.attach(nameLabel, 0, 1, 1, 1);
  grid.attach(nameEntry, 1, 1, 1, 1);
  grid.attach(usernameLabel, 0, 2, 1, 1);
  grid.attach(usernameEntry, 1, 2, 1, 1);
  grid.attach(passwordLabel, 0, 3, 1, 1);
  grid.attach(passwordEntry, 1, 3, 1, 1);
  grid.attach(doneButton, 1, 4, 1, 1);
  grid.show_all();

  passwordEntry.visibility = false;
  passwordEntry.input_purpose = Gtk.InputPurpose.PASSWORD;

  doneButton.clicked.connect(self => assistant.set_page_complete(grid, true));

  return grid;
}

Gtk.Box doPage3(Gtk.Assistant assistant) {
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);
  var progressBar = new Gtk.ProgressBar();

  box.halign = Gtk.Align.CENTER;
  box.valign = Gtk.Align.CENTER;
  box.pack_start(new Gtk.Label("Installing the system..."), false, false, 0);
  box.pack_start(progressBar, false, false, 0);
  box.show_all();

  progressBar.width_request = 240;
  progressBar.pulse_step = 0.2;

  assistant.apply.connect(self => Timeout.add(200, () => {
    var fraction = progressBar.get_fraction();

    if (fraction == 1 || fraction == 1.0) {
      assistant.set_page_complete(box, true);
      assistant.commit();
      return Source.REMOVE;
    } else if (fraction < 0) {
      progressBar.pulse();
    } else {
      progressBar.set_fraction(fraction + 0.1);
    }

    return Source.CONTINUE;
  }));

  return box;
}