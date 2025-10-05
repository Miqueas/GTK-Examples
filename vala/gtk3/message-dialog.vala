const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.MessageDialog";
const string APP_TITLE = "Gtk.MessageDialog";
const string titleText = "<span size='x-large' font-weight='bold'>Universe destruction</span>";
const string summaryText = "Our universe has a lot of problems and the only way to fix it is destroying the entire universe and this important decision is now in your hands.";
const string epilogText = "<span size='large' font-weight='bold'>Do you accept?</span>";

int main(string[] args) {
  var app = new Gtk.Application(APP_ID, 0);
  app.startup.connect(on_app_startup);
  app.activate.connect(on_app_activate);
  return app.run(args);
}

void on_app_activate(Application self) {
  var window = (self as Gtk.Application)?.get_active_window() as Gtk.MessageDialog;
  var response = window?.run();
  window?.destroy();

  switch (response) {
    case Gtk.ResponseType.OK:
      print("Universe destroyed! 💥\n");
      break;
    case Gtk.ResponseType.CANCEL:
      print("Universe is in peace now! 🙏\n");
      break;
    default:
      print("Nothing happens! 🤔\n");
      break;
  }
}

void on_app_startup(Application self) {
  var messageDialog = new Gtk.MessageDialog(
    null,
    Gtk.DialogFlags.MODAL,
    Gtk.MessageType.QUESTION,
    Gtk.ButtonsType.NONE,
    null
  );

  messageDialog.title = APP_TITLE;
  messageDialog.text = titleText;
  messageDialog.use_markup = true;
  messageDialog.secondary_text = summaryText;
  messageDialog.application = self as Gtk.Application;
  messageDialog.add_button("Yes 👍", Gtk.ResponseType.OK);
  messageDialog.add_button("No 🛑", Gtk.ResponseType.CANCEL);
}