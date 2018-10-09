function Engine(win) {
    this.win = win;
    let cvs = win.document.getElementById('cvs');
    this.util = new Utilities(win, cvs);
    this.fractalStack = [];
    this.MAX_ITERATIONS = 10;
    this.CVS_WIDTH = 500;
    this.CVS_HEIGHT = 500;
    this.INTERVAL = 10;
}

Engine.prototype.renderFirst = function() {
    this.util.drawBackground();
    this.util.getContext().lineWidth = 2;
};

Engine.prototype.update = function(util) {
    if (this.fractalStack.length == 0) {
        return;
    }
    
    let line = this.fractalStack[0];
    let iter = line.iter;
    
    if (iter <= this.MAX_ITERATIONS) {
        let x0 = line.x;
        let y0 = line.y;
        let len0 = line.len;
        let ang = line.angle;
        let rad = util.degToRad(ang);
        let hue = line.hue;
        
        // create two brances from this node
        let x1 = line.x - len0 * Math.cos(rad);
        let y1 = line.y - len0 * Math.sin(rad);
        let len1 = len0 * 0.62;
        let ang1A = ang + 60;
        let ang1B = ang - 60;
        let hue1 = hue + 30;
        
        this.fractalStack.push({iter: iter + 1, x: x1, y: y1, len: len1, angle: ang1A, hue: hue1});
        this.fractalStack.push({iter: iter + 1, x: x1, y: y1, len: len1, angle: ang1B, hue: hue1});
    }
    
    this.fractalStack.shift();
};

Engine.prototype.render = function(util) {
    if (this.fractalStack.length == 0) {
        return;
    }
    
    let line = this.fractalStack[0];
    let x0 = line.x;
    let y0 = line.y;
    let len = line.len;
    let ang = line.angle;
    let rad = util.degToRad(ang);
    let x1 = -len * Math.cos(rad);
    let y1 = -len * Math.sin(rad);
    let hue = line.hue;
    
    util.setForegroundColor(`hsl(${hue}, 100%, 50%)`);
    util.setDrawCursor(x0, y0);
    util.strokePolylineXY(0, 0, x1, y1);
};

Engine.prototype.tick = function(util) {
    this.render(util);
    this.update(util);
};

Engine.prototype.run = function() {
    this.util.setCanvasDimensions(this.CVS_WIDTH, this.CVS_HEIGHT);
    this.util.initInputHandlers();
    this.util.hideWindowCursor();
    this.util.setTickFunc(this.tick.bind(this));
    this.util.setTickInterval(this.INTERVAL);
    
    this.fractalStack.push({
        iter: 0,
        x: this.CVS_WIDTH / 2,
        y: this.CVS_HEIGHT,
        len: this.CVS_HEIGHT / 3,
        angle: 90,
        hue: 0,
    });
    
    this.renderFirst();
    this.util.run();
};

window.addEventListener('load', function main() {
    let eng = new Engine(window);
    eng.run();
});