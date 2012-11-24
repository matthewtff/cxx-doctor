define (['jquery', 'ejs', './utils', './gettext'], function ($, ejs, utils, gettext) {

	var module = {
		caption : function (text) {
			if (!text)
				return;
			$("#panel-caption").text(text);
			document.title = text;
		},
		show : function () {
			utils.loadTemplate("/tmpl/top-panel.ejs", ".top-panel");
		}
	}

	gettext.register(module);
	module.show();

	return module;
});
