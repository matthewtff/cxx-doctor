requirejs.config({
	baseUrl: '/js/libs',
	paths: {
		app: '../app'
	}
});

require([
	'jquery',
	'ejs',
	'app/utils',
	'app/panel',
	'app/menu',
	'app/gettext',
	'app/edit-servey',
	'app/edit-patient',
	'app/all-patients',
	'app/edit-doctor'
	],
function ($, ejs, utils, panel, menu, gettext, edit_servey, edit_patient, all_patients, edit_doctor) {

	window.$ = $;
	window.ejs = ejs;
	window.utils = utils;
	window.panel = panel;
	window.menu = menu;
	window.gettext = gettext;
	window.edit_servey = edit_servey;
	window.edit_patient = edit_patient;
	window.all_patients = all_patients;
	window.edit_doctor = edit_doctor;

});
