define (['jquery', 'ejs', './utils', './menu'], function ($, ejs, utils, menu) {

	var report_callbacks = {
		"abdomen" : "collectAbdomenData"
	};

	return {
		getCurrentServey : function () {
			if ($("#patient-id").length === 0) // no current servey...
				return {};

			var inputs = $(".edit-servey_input");
			var servey = {};

			inputs.each(function (nth) {
				var el = inputs[nth];
				servey[el.name] = el.value;
			});
			return servey;
		},
		loadServeyByPatient : function (patient_id) {
			var query = "/inmate/get?" + utils.objectToQuery({
				id : patient_id
			});

			$.get(query, function (data) {
				if (!data.inmates.length)
					return;
				var servey = window.edit_servey.getCurrentServey();
				var patient = data.inmates[0];
				servey.patient = patient.surname + ' ' + patient.name + ' ' + patient.second_name;
				servey.patient_id = patient.id;
				window.menu.showEditServey(servey);
			});
		},
		loadServeyByDisease : function (disease_key) {
			var query = "/disease/get?" + utils.objectToQuery({
				key : disease_key
			});

			$.get(query, function (data) {
				if (!data.diseases.length)
					return;
				var servey = window.edit_servey.getCurrentServey();
				var disease = data.diseases[0];
				servey.diagnosis = disease.value;
				servey.diagnosis_key = disease.key;
				window.menu.showEditServey(servey);
			});
		},
		searchPatients : function () {
			var patient_input = $('#patient-search-string');
			var query = "/inmate/search?" + utils.objectToQuery({
				search_string : patient_input.val()
			});

			$.get(query, function (inmates) {
				utils.loadTemplate("/tmpl/patient-search-list.ejs",
					".edit-servey_patient-list", inmates);
			});

		},
		searchDiagnosis : function () {
			var diagnosis_input = $('#diagnosis-search-string');
			var query = "/disease/search?" + utils.objectToQuery({
				search_string : diagnosis_input.val()
			});

			$.get(query, function (diagnosis) {
				utils.loadTemplate("/tmpl/diagnosis-search-list.ejs",
					".edit-servey_diagnosis-list", diagnosis);
			});
		},
		toggleType : function (type, el) {
			$(el).toggleClass("edit-servey-type-choice-active");

			var selector = ".edit-servey-type-field-" + type;
			var template_url = "/tmpl/edit-servey-" + type + ".ejs";
			$(selector).html( new EJS({url : template_url}).render({}) );
			$(selector).slideToggle();
		},
		createReport : function () {
			var active = $(".edit-servey-type-choice-active");
			var collected_data = $.map(active, function (element) {
				var name = $(element).attr("data");
				return eval(report_callbacks[name])();
			});

			var servey_info = $.map( $(".edit-servey_input"), function (element) {
				return {
					name : element.name,
					value : element.value
				};
			});

			var servey_data = {
				types : {}
			};
			for (var counter = 0; counter < collected_data.length; ++counter)
				servey_data.types[collected_data[counter].type] = collected_data[counter].data;
			for (var counter = 0; counter < servey_info.length; ++counter)
				servey_data[servey_info[counter].name] = servey_info[counter].value;
			servey_data.report = $(".edit-servey-report-text").val();
			console.log(servey_data);
			utils.loadTemplate("/tmpl/servey-report.ejs", ".workspace", {servey: servey_data});
		}
	}

});
