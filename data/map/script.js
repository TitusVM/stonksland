document.addEventListener("click", function(e) {
	e = e || window.event;
	var target = e.target || e.srcElement,
		text = target.textContent || target.innerText;
	if (target.tagName == "path") {
		var name = null;
		if (target.hasAttribute("name")) {
			name = target.getAttribute("name");
		} else if (target.hasAttribute("class")) {
			name = target.getAttribute("class");
		}
		
		window.countryClickedJs(name);
	}
}, false);

function highlightCountry(countryName) {
	var paths = document.getElementsByName(countryName);
	if (paths.length == 0) {
		paths = document.getElementsByClassName(countryName);
	}
	if (paths.length == 0) {
		alert("Erreur");
	}

	for (let item of paths) {
		item.setAttribute("fill", "red");
	}
}

function resetMap() {
	for (let path of document.getElementsByTagName("path")) {
		if (path.hasAttribute("fill")) {
			path.removeAttribute("fill");
		}
	}
}

function resizeMap(width) {
	document.getElementById("map").setAttribute("width", width);
}

new QWebChannel(qt.webChannelTransport, function(channel) {
	var qtMap = channel.objects.qtMap;
	qtMap.highlightJs.connect(highlightCountry);
	qtMap.resetJs.connect(resetMap);
	qtMap.resizeMapJs.connect(resizeMap);
	window.countryClickedJs = qtMap.countryClickedJs;

	qtMap.connectedJs(); // tell the app the connection is established
});