define (['jquery', 'ejs', './utils', './panel', './gettext'], function ($, ejs, utils, panel, gettext) {

	var menu_active_class = "main-menu_entry-active";

	var module = {
		show : function (info) {

			utils.loadTemplate("/tmpl/main-menu.ejs", ".main-menu");

			$(".main-menu_entry").click(function () {
				$(".main-menu_entry").removeClass(menu_active_class);
				$(this).toggleClass(menu_active_class);
			});
			this.clearWorkspace();
			if (info && info.gettext)
				this.showSettings();
		},
		showEditServey : function (servey) {
			utils.loadTemplate("/tmpl/edit-servey.ejs", ".workspace", {
				servey : (servey ? servey : {})
			});
			panel.caption(_T("Edit servey"));
		},
		showEditPatient : function (patient) {
			utils.loadTemplate("/tmpl/edit-patient.ejs", ".workspace", {
				patient : (patient ? patient : {})
			});
			panel.caption(_T("Edit patient"));
			//TODO: Плохое орешение переключения активного меню.
			$(".main-menu_entry").removeClass(menu_active_class);
			$(".main-menu_entry:nth-child(6)").toggleClass(menu_active_class);
		},
		showAllPatients : function () {
			utils.loadTemplate("/tmpl/all-patients.ejs", ".workspace", "/inmate/all");
			panel.caption(_T("All patients"));
		},
		showHelp : function () {
			this.clearWorkspace("/tmpl/" + gettext.getLanguage() + "-help.ejs");
			panel.caption(_T("Help"));
		},
		clearWorkspace : function (url) {
			var selector = ".workspace";
			var greeting = url ? url : "/tmpl/" + gettext.getLanguage() + "-greeting.ejs";
			utils.loadTemplate(greeting, selector);
			if (!url) {
				panel.caption(_T("Main"));
				$(".main-menu_entry").removeClass(menu_active_class);
				$(".main-menu_entry:nth-child(1)").toggleClass(menu_active_class);
			}
		},
		showSettings : function () {
			utils.loadTemplate("/tmpl/settings.ejs", ".workspace");
			panel.caption(_T("Settings"));
			$(".main-menu_entry").removeClass(menu_active_class);
			$(".main-menu_entry:nth-child(2)").toggleClass(menu_active_class);
		},
		showEditDoctor : function () {
			utils.loadTemplate("/tmpl/edit-doctor.ejs", ".workspace");
			panel.caption(_T("Doctor"));
		}
	}

	gettext.register(module);
	module.show();

	return module;
});
