//remove todos os erros que foram exibidos
function removeErrors(idName) {
    for (let i = 0; i < 4; i++) {
        var elem = document.getElementById(`${idName}${i}`);
        if (elem)
            elem.parentNode.removeChild(elem);
    }
}

//renderiza todos os erros que forem passados
function renderErrors(_err, container, idName) {
    if (_err.length > 0) {
        const html = document.getElementById(container)

        _err.map((e, id) => {
            var node = document.createElement("span");
            node.id = `${idName}${id}`
            var textnode = document.createTextNode(e);

            node.appendChild(textnode);
            html.append(node);
        })
    }
}