define (['jquery', './utils'], function ($, utils) {

	var dictionary = [];
	var language = "en";

	var settings = utils.syncAjax("/settings/get");

	if (settings.lang)
		language = settings.lang;

	/**
	 * Для смены языка onfly будем использовать такую схему:
	 * 1. Каждый модуль должен иметь метод show который заменяет его
	 * отображение в соответствии с новыми настройками.
	 * 2. Каждый модуь, который хочет что бы его перегружали с новыми
	 * настройками должен зарегистрироваться.
	 * 3. Когда настройки изменяются - перегружаем все зарегистрированые
	 * модули.


	 	Для того что бы модуль знал что его перегружает именно
		gettext - последний обязуется передавать объект с полем gettext
		равным true.
	 */
	var registered_modules = [];

	var ret = {
		gettext : function (text) {
			if (dictionary[text])
				return dictionary[text];
			else
				return text;
		},
		setLanguage : function (lang) {
			if (!lang)
				return;
			language = lang;
			var query = "/lang/" + language + ".json";
			// Тут важно сделать именно синхронный запрос.
			$.ajax(query, {async : false}).done(function (data) {
				dictionary = data.dictionary;
			});
			registered_modules.forEach(function (module) {
				module.show({gettext : true});
			});
		},
		getLanguage : function () {
			return language;
		},
		register : function (module) {
			registered_modules.push(module);
		},
		dateToLocal : function (date) {
			var local = new Date(date);
			return local.toLocaleDateString();
		}
	}

	window._T = ret.gettext;

	ret.setLanguage(language);

	return ret;
});
