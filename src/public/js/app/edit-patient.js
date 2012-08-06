define (['jquery', 'ejs', './utils', './menu'], function ($, ejs, utils, menu) {

	return {
		register : function () {
			var patient_data = {};
			var error = "";
			$.each($('.edit-patient_input'), function (nth, el) {
				patient_data[el.name] = el.value;
			});

			if (!patient_data.name || !patient_data.surname)
				error = "Not enough data";

			if (error.length) {
				utils.showMessage(_T(error), _T("Error"));
				return;
			}
			if (patient_data.insurance == "nothing-selected" && patient_data.insurance_manual != "") {
				$.get("/insurance/new?name=" + patient_data.insurance_manual);
				patient_data.insurance = patient_data.insurance_manual;
			}

			var query = patient_data.id ? "/inmate/edit?" : "/inmate/new?";
			query += utils.objectToQuery(patient_data);
			$.get(query, function(data) {
				if (data.answer != "success")
					utils.showMessage(_T(data.answer), _T("Error"));
				else {
					if (patient_data.id)
						menu.clearWorkspace();
					else {
						window.menu.showEditServey({
							patient : patient_data.surname + " " + patient_data.name + " " + patient_data.second_name,
							patient_id : data.id
						});
					}
				}
			});
		},
		del : function(patient_id) {
			var query = "/inmate/del?" + utils.objectToQuery({id : patient_id});
			$.get(query, function(answer) {
				if (answer != "success")
					utils.showMessage(_T(answer), _T("Error"));
				else
					menu.clearWorkspace();
			});
		}
	}

});
