$.ajax({
	type: "POST",
	url: "api/log.php",
	timeout: 2000,
	cache: false,
	success: function(r) {
		$.each(r.log, function(i, log) {
			console.log(log);
			if(log.event.tr == 0) {
				$("#events").prepend("<tr><td>"+log.event.id+"</td><td>"+log.event.measurement+"</td><td>"+log.event.userid+"</td><td>"+log.event.tr+"</td></tr>");
			} else {
				$("#events").prepend("<tr class=\"danger\"><td>"+log.event.id+"</td><td>"+log.event.measurement+"</td><td>"+log.event.userid+"</td><td>"+log.event.tr+"</td></tr>");

			}
		});
		recursively_ajax();
	},
	error: function(xhs, textStatus, errorThrown) {
		if(xhr.status === 404) {
			$("#errorMessage").show();
			$("#errorMessage").html("Error: "+errorThrown);
		}
	}
});