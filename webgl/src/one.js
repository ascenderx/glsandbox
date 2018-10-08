function gel(id) {
    return document.getElementById(id);
}

let player = {
    vertices: [
        [0, -10], [-10, 10], [10, 10],
    ],
    rotation: 0,
    direction: 0,
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
    if (util.isKeyDown('p') || util.isMouseButtonDown(UTIL_MOUSE_RIGHT)) {
        util.togglePause();
        util.debounceKey('p');
        util.debounceMouseButton(UTIL_MOUSE_RIGHT);
        
        if (util.isPaused()) {
            player.color = '#0af';
        } else {
            player.color = '#f00';
        }
    }
    
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
    
    if (util.isKeyDown('a')) {
        player.rotation -= 5;
        player.vertices = util.rotatePts(player.vertices, -5);
    } else if (util.isKeyDown('d')) {
        player.rotation += 5;
        player.vertices = util.rotatePts(player.vertices, +5);
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
    util.drawBackground();
    util.getContext().lineWidth = 3;
    
    // player
    util.setForegroundColor(player.color);
    let cursor = player.coords;
    util.setDrawCursor(cursor.x, cursor.y);
    util.strokePolygonPts(player.vertices);
    // player point
    util.setForegroundColor('#ff0');
    util.setDrawCursor(cursor.x, cursor.y);
    util.drawPoint();
    
    // cursor
    let cursorX = util.getMouseX();
    let cursorY = util.getMouseY();
    util.setForegroundColor('#0af');
    util.setDrawCursor(cursorX, cursorY);
    util.strokePolygonXY(0, -20, 0, 20);
    util.strokePolygonXY(-20, 0, 20, 0);
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
    util.setTickInterval(20);
    util.run();
    
    window.util = util;
}

window.addEventListener('load', main);