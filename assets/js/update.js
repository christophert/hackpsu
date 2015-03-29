$.ajax({
	type: "POST",
	url: "api/log.php",
	timeout: 2000,
	cache: false,
	success: function(r) {
		$.each(r.log, function(i, log) {
			$("#events").prepend("<tr><td>"+log.entry.id+"</td><td>"+log.entry.measurement+"</td><td>"+log.entry.userid+"</td><td>"+log.entry.tr+"</td></tr>");
		});
	},
	error: function(xhs, textStatus, errorThrown) {
		if(xhr.status === 404) {
			$("#errorMessage").show();
			$("#errorMessage").html("Error: "+errorThrown);
		}
	}
});