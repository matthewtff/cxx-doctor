function objectToQuery(obj) {
	if (typeof obj !== "object")
		throw new Error("bad object");

	var query = "";
	for (attr in obj) {
		var attrType = typeof obj[attr];
		if (attrType === "function")
			query += attr + "=" + obj[attr]() + "&";
		else if (attrType !== "object")
			query += attr + "=" + obj[attr] + "&";
	}
	return query;
}

function makeSearchRequest(searchQuery, callback) {
	if (typeof searchQuery !== "string")
		callback("bad query");
	
	var query = "/inmate/search?search_string=" + searchQuery; 

	$.get(query, function(data) {
		callback(undefined, data);
	}).fail(function() {
		callback("request error");
	});
}

function makeFindAllRequest(callback) {
	$.get("/inmates/all", function(data) {
		callback(undefined, data);
	}).fail(function() {
		callback("request error");
	});
}

function makeCreateRequest(newPatient, callback) {
	if (typeof newPatient !== 'object')
		callback("bad patient");

	var query = "/inmate/new?" + objectToQuery(newPatient);
	$.get(query, function(data) {
		callback(undefined, data);
	}).fail(function() {
		callback("request error");
	});
}

function makeRemoveRequest(patientId, callback) {
	if (typeof patientId !== "string")
		callback("bad patient id");

	var query = "/inmates/del?id=" + patientId;

	$.get(query, function(data) {
		callback(undefined, data);
	}).fail(function() {
		callback("request error");
	});
}

function decorateDate(dateString) {
	var date = new Date(dateString);
	return date.toLocaleDateString();
}

function fullYears(date) {
	var from = new Date(date);
	var now = new Date();
	return Math.floor((now - from) / 1000 / 60 / 60 / 24 / 365.25);
}

function goHome() {
	window.location = '/html/index.html';
}

function isEmpty(str) {
	if (typeof str !== "string")
		throw new Error("bad argument");
	
	return str.length === 0;
}

$(function(){

	function PatientViewModel() {
		var self = this;
		
		self.newPatient = ko.observable({
			name : ko.observable(""),
			surname : ko.observable(""),
			second_name : ko.observable(""),
			address : ko.observable(""),
			card : ko.observable(""),
			sex : ko.observable("male"),
			date : ko.observable("18.02.2012")
		});

		self.searchResult = ko.observableArray([]);

		self.showNewPatient = function() {
			$(".left-menu-find-patient").removeClass("active");
			$(".find-patient").hide();
			$(".left-menu-new-patient").addClass("active");
			$(".new-patient").show();
		}

		self.showPatientSearch = function() {
			$(".left-menu-new-patient").removeClass("active");
			$(".new-patient").hide();
			$(".left-menu-find-patient").addClass("active");
			$(".find-patient").show();
		}

		self.findPatient = function() {
			var searchQuery = $(".find-patient .search-query").val();
			makeSearchRequest(searchQuery, function(err, result) {
				if (err) {
					self.searchResult([]);
					console.log("Error requesting search query: " + err);
					return;
				}
				self.searchResult(result["inmates"]);
			});
		}

		self.findAll = function() {
			makeFindAllRequest(function(err, result) {
				if (err) {
					self.searchResult([]);
					console.log("Error requesting all inmates: " + err);
					return;
				}
				self.searchResult(result["inmates"]);
			});
		}

		self.createPatient = function() {
			makeCreateRequest(self.newPatient(), function(err, result) {
				if (err) {
					console.log("Error creating new inmate: " + err);
					return;
				}
				goHome();
			});
		}

		self.removePatient = function(patient) {
			makeRemoveRequest(patient.id, function(err) {
				if (err) {
					console.lof("Error removing patient: " + err);
					return;
				}
				var patientsLeft = self.searchResult();
				for (var count in patientsLeft) {
					if (patientsLeft[count] === patient) {
						patientsLeft.splice(count, 1);
						break;
					}
				}
				self.searchResult(patientsLeft);
			});
		}

	}
	$(".date").datepicker();
	ko.applyBindings(new PatientViewModel());
});
