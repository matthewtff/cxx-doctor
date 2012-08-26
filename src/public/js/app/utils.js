define (['jquery', 'ejs'], function ($, ejs) {

	var popup_selector = ".popup-window";

	return {
		loadTemplate : function (template_url, selector, url_or_data) {
			if (typeof url_or_data == "string") {
				$.get(url_or_data, function (data) {
					/*utils.loadTemplate("/tmpl/all-patients.ejs",
						".workspace", data);*/
					utils.loadTemplate(template_url, selector, data);
				});
			} else {
				$(selector).hide();
				$(selector).html( new EJS({url : template_url}).render(url_or_data) );
				$(selector).slideDown();
			}
		},
		objectToQuery : function (obj) {
			var query = "";
			for (var prop in obj) {
				query += prop + "=" + obj[prop] + "&";
			}
			return query;
		},
		showMessage : function (text, caption) {
			$(".popup-window-text").text(text);
			$(".popup-window-title").text(caption ? caption : _T("Message"));
			$(popup_selector).slideDown();
			setTimeout(this.hideMessage, 1000);
		},
		hideMessage : function () {
			$(popup_selector).slideUp();
		},
		syncAjax : function (url) {
			var ret;
			$.ajax(url, {async : false}).done(function (data) {
				ret = data;
			});
			return ret;
		},
		htmlDate : function () {
			// Code from http://stackoverflow.com/questions/6982692/html5-input-type-date-default-value-to-today
			var now = new Date();
			var month = (now.getMonth() + 1);               
			var day = now.getDate();
			if(month < 10) 
				month = "0" + month;
			if(day < 10) 
				day = "0" + day;
			var today = now.getFullYear() + '-' + month + '-' + day;
			return today;
		}
	}

});
