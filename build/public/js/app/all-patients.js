define (['jquery', './utils', './menu'], function ($, utils, menu) {

	return {
		load : function (patient_id) {
			var query = "/inmate/get?id=" + patient_id;
			$.get(query, function (data) {
				menu.showEditPatient(data.inmates[0]);
			});
		}
	}

});
