import gi, sys
gi.require_version("Gtk", "3.0")
from gi.repository import GLib, Gtk

appID = "io.github.Miqueas.GTK-Examples.Python.Gtk3.Assistant"
appTitle = "Gtk.Assistant"
appWelcomeText = "<span font='Bold 16'>Welcome to the GtkAssistant example</span>"

def onAssistantApply(progressBar, window, box):
    fraction = progressBar.get_fraction()

    if fraction == 1 or fraction == 1.0:
        window.set_page_complete(box, True)
        window.commit()
        return False
    elif fraction < 0: progressBar.pulse()
    else: progressBar.set_fraction(fraction + 0.1)

    return True

def buildPage2(window):
    grid = Gtk.Grid(column_spacing = 10, row_spacing = 10, halign = Gtk.Align.CENTER, valign = Gtk.Align.CENTER)
    infoLabel = Gtk.Label(label = "Fill this form")
    nameLabel = Gtk.Label(label = "Full name")
    usernameLabel = Gtk.Label(label = "Username")
    passwordLabel = Gtk.Label(label = "Password")
    nameEntry = Gtk.Entry()
    usernameEntry = Gtk.Entry()
    passwordEntry = Gtk.Entry(visibility = False, input_purpose = Gtk.InputPurpose.PASSWORD)
    doneButton = Gtk.Button(label = "Done")

    grid.attach(infoLabel, 0, 0, 2, 1)
    grid.attach(nameLabel, 0, 1, 1, 1)
    grid.attach(nameEntry, 1, 1, 1, 1)
    grid.attach(usernameLabel, 0, 2, 1, 1)
    grid.attach(usernameEntry, 1, 2, 1, 1)
    grid.attach(passwordLabel, 0, 3, 1, 1)
    grid.attach(passwordEntry, 1, 3, 1, 1)
    grid.attach(doneButton, 1, 4, 2, 1)
    grid.show_all()

    doneButton.connect("clicked", lambda _: window.set_page_complete(grid, True))
    return grid

def buildPage3(window):
    progressBar = Gtk.ProgressBar(width_request = 240, pulse_step = 0.2)
    box = Gtk.Box(
        orientation = Gtk.Orientation.VERTICAL,
        spacing = 10,
        halign = Gtk.Align.CENTER,
        valign = Gtk.Align.CENTER
    )

    box.pack_start(Gtk.Label(label = "Installing the system"), False, False, 0)
    box.pack_start(progressBar, False, False, 0)
    box.show_all()

    window.connect("apply", lambda _: GLib.timeout_add(200, onAssistantApply, progressBar, window, box))
    return box

def onAppStartup(self):
    window = Gtk.Assistant(application = self, title = appTitle)
    page1 = Gtk.Label(visible = True, label = appWelcomeText, use_markup = True)
    page2 = buildPage2(window)
    page3 = buildPage3(window)
    page4 = Gtk.Label(visible = True, label = "Installation complete")

    window.set_title(appTitle)
    window.set_default_size(800, 400)
    window.connect("close", Gtk.Widget.destroy)
    window.connect("cancel", Gtk.Widget.destroy)
    window.append_page(page1)
    window.append_page(page2)
    window.append_page(page3)
    window.append_page(page4)
    window.set_page_title(page1, "Welcome")
    window.set_page_title(page2, "Create account")
    window.set_page_title(page3, "Installation")
    window.set_page_title(page4, "Summary")
    window.set_page_type(page1, Gtk.AssistantPageType.INTRO)
    window.set_page_type(page2, Gtk.AssistantPageType.CONFIRM)
    window.set_page_type(page3, Gtk.AssistantPageType.PROGRESS)
    window.set_page_type(page4, Gtk.AssistantPageType.SUMMARY)
    window.set_page_complete(page1, True)

app = Gtk.Application(application_id = appID, flags = 0)
app.connect("activate", lambda self: self.get_active_window().present())
app.connect("startup", onAppStartup)

sys.exit(app.run(sys.argv))