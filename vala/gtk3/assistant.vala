const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.Assistant";
const string appTitle = "GtkAssistant";
const string appWelcomeText = "<span font='Bold 16'>Welcome to the GtkAssistant example</span>";

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
  var headerBar = new Gtk.HeaderBar();
  var page1 = new Gtk.Label(appWelcomeText) { visible = true, use_markup = true };
  var page2 = doPage2(window);
  var page3 = doPage3(window);
  var page4 = new Gtk.Label("System installed successfully!") { visible = true };

  (self as Gtk.Application)?.add_window(window);

  with (window) {
    set_titlebar(headerBar);
    set_default_size(800, 400);
    cancel.connect(destroy);
    close.connect(destroy);

    append_page(page1);
    append_page(page2);
    append_page(page3);
    append_page(page4);

    set_page_title(page1, "Welcome");
    set_page_title(page2, "Create account");
    set_page_title(page3, "Installing system");
    set_page_title(page4, "Summary");

    set_page_type(page1, Gtk.AssistantPageType.INTRO);
    set_page_type(page2, Gtk.AssistantPageType.CONFIRM);
    set_page_type(page3, Gtk.AssistantPageType.PROGRESS);
    set_page_type(page4, Gtk.AssistantPageType.SUMMARY);

    set_page_complete(page1, true);
  }

  with (headerBar) {
    visible = true;
    subtitle = appTitle;
    show_close_button = true;
  }
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

  with (grid) {
    column_spacing = 10;
    row_spacing = 10;
    halign = Gtk.Align.CENTER;
    valign = Gtk.Align.CENTER;
    attach(infoLabel, 0, 0, 2, 1);
    attach(nameLabel, 0, 1, 1, 1);
    attach(nameEntry, 1, 1, 1, 1);
    attach(usernameLabel, 0, 2, 1, 1);
    attach(usernameEntry, 1, 2, 1, 1);
    attach(passwordLabel, 0, 3, 1, 1);
    attach(passwordEntry, 1, 3, 1, 1);
    attach(doneButton, 1, 4, 1, 1);
    show_all();
  }

  passwordEntry.visibility = false;
  passwordEntry.input_purpose = Gtk.InputPurpose.PASSWORD;

  doneButton.clicked.connect(self => assistant.set_page_complete(grid, true));

  return grid;
}

Gtk.Box doPage3(Gtk.Assistant assistant) {
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);
  var progressBar = new Gtk.ProgressBar();

  with (box) {
    halign = Gtk.Align.CENTER;
    valign = Gtk.Align.CENTER;
    pack_start(new Gtk.Label("Installing the system..."), false, false, 0);
    pack_start(progressBar, false, false, 0);
    show_all();
  }

  with (progressBar) {
    width_request = 240;
    pulse_step = 0.2;
  }

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