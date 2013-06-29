define(['jquery', 'knockout'], function($, ko) {

return {

	sync : function(url) {
		return $.ajax(url, {async : false}).done(function(data) {
			return data;
		});
	},

	async : function(url, callback) {
		$.get(url, callback);
	}

};

});
