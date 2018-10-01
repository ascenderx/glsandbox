function gel(id) {
    return document.getElementById(id);
}

let player = {
    vertices: [
        [0, -10], [-10, 10], [10, 10],
    ],
    coords: {x: 200, y: 200},
    color: '#f00',
};

let game = {
    player: player,
    paused: false,
    width: 500,
    height: 500,
};

function init(util) {
    util.setCanvasDimensions(game.width, game.height);
    util.initInputHandlers();
    util.hideWindowCursor();
}

function input(util) {
    if (util.isPaused()) {
        return;
    }
    
    if (util.isKeyDown('ArrowRight')) {
        player.coords.x += 5;
    } else if (util.isKeyDown('ArrowLeft')) {
        player.coords.x -= 5;
    }
    
    if (util.isKeyDown('ArrowDown')) {
        player.coords.y += 5;
    } else if (util.isKeyDown('ArrowUp')) {
        player.coords.y -= 5;
    }
}

function wrap(entity) {
    if (entity.coords.x > game.width) {
        entity.coords.x = 0;
    } else if (entity.coords.x < 0) {
        entity.coords.x = game.width;
    }
    
    if (entity.coords.y > game.height) {
        entity.coords.y = 0;
    } else if (entity.coords.y < 0) {
        entity.coords.y = game.height;
    }
}

function update(util) {
    wrap(player);
}

function render(util) {
    if (util.isPaused()) {
        return;
    }

    util.drawBackground();
    
    util.getContext().lineWidth = 3;
    
    util.setForegroundColor(player.color);
    let cursor = player.coords;
    util.setDrawCursor(cursor.x, cursor.y);
    util.strokePolygonPts(player.vertices);
    
    util.setForegroundColor('#ff0');
    util.setDrawCursor(cursor.x, cursor.y);
    util.drawPoint();
}

function tick(util) {
    input(util);
    update(util);
    render(util);
}

function main() {
    let util = new Utilities(window, gel('cvs'));
    
    init(util);
    util.setTickFunc(tick);
    util.setTickInterval(30);
    util.run();
    
    window.util = util;
}

window.addEventListener('load', main);