define (['jquery', './utils', './menu'], function ($, utils, menu) {

	return {
		register : function () {
			var doctor_info = {};
			$.each($(".edit-doctor-input"), function (index, element) {
				doctor_info[element.name] = element.value;
			});
			var query = "/register/?" + utils.objectToQuery(doctor_info);
			$.get(query, function (err) {
				if (err != "success")
					utils.showMessage(_T(err), _T("Error"));
				else
					menu.clearWorkspace();
			});
		},
		del : function() {
		}
	}

});
