function Engine(win) {
    this.win = win;
    let cvs = win.document.getElementById('cvs');
    this.util = new Utilities(win, cvs);
    this.fractalStack = [];
    this.CVS_WIDTH = 600;
    this.CVS_HEIGHT = 600;
    this.INTERVAL = 10;
    this.numSpokes = null;
    this.shrinkRatio = null;
    this.angleDelta = null;
    this.maxIterations = null;
    this.hueDelta = 30;
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
    
    if (iter < this.maxIterations) {
        let x0 = line.x;
        let y0 = line.y;
        let len0 = line.len;
        let ang = line.angle;
        let rad = Utilities.degToRad(ang);
        let hue = line.hue;
        
        // create two brances from this node
        let x1 = line.x - len0 * Math.cos(rad);
        let y1 = line.y - len0 * Math.sin(rad);
        let len1 = len0 * this.shrinkRatio;
        let ang1A = ang + this.angleDelta;
        let ang1B = ang - this.angleDelta;
        let hue1 = hue + this.hueDelta;
        
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
    let rad = Utilities.degToRad(ang);
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

const PHI = (1 + Math.sqrt(5)) / 2.0;

Engine.prototype.run = function() {
    this.util.setCanvasDimensions(this.CVS_WIDTH, this.CVS_HEIGHT);
    this.util.initInputHandlers();
    this.util.hideWindowCursor();
    this.util.setTickFunc(this.tick.bind(this));
    this.util.setTickInterval(this.INTERVAL);
    
    this.maxIterations = 8;
    this.numSpokes = 3;
    this.shrinkRatio = PHI - 1;
    this.angleDelta = 360.0 / this.numSpokes / 2;
    
    let da = this.angleDelta * 2;
    for (let i = 0; i < this.numSpokes; i++) {
        this.fractalStack.push({
            iter: 1,
            x: this.CVS_WIDTH / 2,
            y: this.CVS_HEIGHT / 2,
            len: this.CVS_HEIGHT * (17/80),
            angle: 90 - (i * da),
            hue: 0,
        });
    }
        
    this.renderFirst();
    this.util.run();
};

window.addEventListener('load', function main() {
    let eng = new Engine(window);
    eng.run();
});