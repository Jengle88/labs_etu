class Tetramino {
    /*
        +----+
        |    |
        |  * |  - точка поворота (x = 3, y = 2)
        |    |
        |    |
        +----+
    */
    constructor(state, xRotatePoint, yRotatePoint) {
        this.state = state // в каком из состояний поворота находится
        this.xRotatePoint = xRotatePoint
        this.yRotatePoint = yRotatePoint
    }

    drawOnField(field, mapOfState, color) {
        if (this.#checkDraw(field, mapOfState, UIEditor.clearElemColor)) {
            let xStart = this.xRotatePoint - 2
            let yStart = this.yRotatePoint - 1
            let figure = mapOfState.get(this.state.toString())
            for (let dx = 0; dx < figure[0].length; dx++) {
                for (let dy = 0; dy < figure.length; dy++) {
                    if (figure[dy][dx] === '*') {
                        if (0 <= xStart + dx && xStart + dx < field[0].length &&
                            0 <= yStart + dy && yStart + dy < field.length) {
                            field[yStart + dy][xStart + dx] = color
                        }
                    }
                }
            }
            return true
        } else
            return false
    }

    #checkDraw(field, mapOfState, clearElement = UIEditor.clearElemColor) {
        let xStart = this.xRotatePoint - 2
        let yStart = this.yRotatePoint - 1
        let figure = mapOfState.get(this.state.toString())
        for (let dx = 0; dx < figure[0].length; dx++) {
            for (let dy = 0; dy < figure.length; dy++) {
                if (figure[dy][dx] === '*') {
                    const x = xStart + dx
                    const y = yStart + dy
                    if (!(0 <= x && x < field[0].length && 0 <= y && y < field.length && field[y][x] === clearElement)) {
                        return false
                    }
                }
            }
        }
        return true
    }

    clearOnField(field, mapOfState, clearElement = UIEditor.clearElemColor) {
        let xStart = this.xRotatePoint - 2
        let yStart = this.yRotatePoint - 1
        let figure = mapOfState.get(this.state.toString())
        for (let dx = 0; dx < figure[0].length; dx++) {
            for (let dy = 0; dy < figure.length; dy++) {
                if (figure[dy][dx] === '*') {
                    if (0 <= xStart + dx && xStart + dx < field[0].length &&
                        0 <= yStart + dy && yStart + dy < field.length) {
                        field[yStart + dy][xStart + dx] = clearElement
                    }
                }
            }
        }
    }

    moveDown(field, mapOfState, color) {
        this.clearOnField(field, UIEditor.clearElemColor)
        if (this.#checkMoveDown(field, mapOfState)) {
            this.yRotatePoint++
        } else {
            this.drawOnField(field, mapOfState, color)
            return false
        }
        return this.drawOnField(field, mapOfState, color)
    }

    #checkMoveDown(field, mapOfState, clearElement = UIEditor.clearElemColor) {
        let xStart = this.xRotatePoint - 2
        let yStart = this.yRotatePoint
        let figure = mapOfState.get(this.state.toString())
        return this.#checkNewPosition(figure, field, xStart, yStart, clearElement)
    }

    moveRight(field, mapOfState, color) {
        this.clearOnField(field, UIEditor.clearElemColor)
        if (this.#checkMoveRight(field, mapOfState)) {
            this.xRotatePoint++
        } else {
            this.drawOnField(field, mapOfState, color)
            return false
        }
        return this.drawOnField(field, mapOfState, color)
    }

    #checkMoveRight(field, mapOfState, clearElement = UIEditor.clearElemColor) {
        let xStart = this.xRotatePoint - 1
        let yStart = this.yRotatePoint - 1
        let figure = mapOfState.get(this.state.toString())
        return this.#checkNewPosition(figure, field, xStart, yStart, clearElement);
    }

    moveLeft(field, mapOfState, color) {
        this.clearOnField(field, UIEditor.clearElemColor)
        if (this.#checkMoveLeft(field, mapOfState)) {
            this.xRotatePoint--
        } else {
            this.drawOnField(field, mapOfState, color)
            return false
        }
        return this.drawOnField(field, mapOfState, color)

    }

    #checkMoveLeft(field, mapOfState, clearElement = UIEditor.clearElemColor) {
        let xStart = this.xRotatePoint - 3
        let yStart = this.yRotatePoint - 1
        let figure = mapOfState.get(this.state.toString())
        return this.#checkNewPosition(figure, field, xStart, yStart, clearElement);
    }

    #checkNewPosition(figure, field, xStart, yStart, clearElement) {
        for (let dx = 0; dx < figure[0].length; dx++) {
            for (let dy = 0; dy < figure.length; dy++) {
                if (figure[dy][dx] === '*') {
                    if (0 <= xStart + dx && xStart + dx < field[0].length &&
                        0 <= yStart + dy && yStart + dy < field.length) {
                        if (field[yStart + dy][xStart + dx] !== clearElement)
                            return false
                    } else
                        return false
                }
            }
        }
        return true
    }

    rotateOnField(field, mapOfState, color) {
        this.clearOnField(field, UIEditor.clearElemColor)
        if (this.#checkRotate(field, mapOfState)) {
            this.state = (this.state + 1) % mapOfState.size
        } else {
            this.drawOnField(field, mapOfState, color)
            return false
        }
        return this.drawOnField(field, mapOfState, color)

    }

    #checkRotate(field, mapOfState, clearElement = UIEditor.clearElemColor) {
        let xStart = this.xRotatePoint - 2
        let yStart = this.yRotatePoint - 1
        let newFigure = mapOfState.get(((this.state + 1) % mapOfState.size).toString())
        return this.#checkNewPosition(newFigure, field, xStart, yStart, clearElement)
    }
}


class OTetramino extends Tetramino {
    static color = "#ec1920"
    static mapOfStates = new Map(Object.entries({
        0: ["....",
            ".**.",
            ".**.",
            "...."],
    }))

    constructor(xRotatePoint, yRotatePoint) {
        super(0, xRotatePoint, yRotatePoint);
    }

    drawOnField(field) {
        return super.drawOnField(field, OTetramino.mapOfStates, OTetramino.color)
    }

    clearOnField(field, clearElement) {
        super.clearOnField(field, OTetramino.mapOfStates, clearElement)
    }

    moveDown(field) {
        return super.moveDown(field, OTetramino.mapOfStates, OTetramino.color);
    }

    moveRight(field) {
        return super.moveRight(field, OTetramino.mapOfStates, OTetramino.color);
    }

    moveLeft(field) {
        return super.moveLeft(field, OTetramino.mapOfStates, OTetramino.color);
    }

    rotateOnField(field) {
        return super.rotateOnField(field, OTetramino.mapOfStates, OTetramino.color);
    }
}

class ITetramino extends Tetramino {
    static color = "#1b77ce"
    static mapOfStates = new Map(Object.entries({
        0: ["..*.",
            "..*.",
            "..*.",
            "..*."],
        1: ["....",
            "****",
            "....",
            "...."]
    }))

    constructor(xRotatePoint, yRotatePoint) {
        super(0, xRotatePoint, yRotatePoint);
    }

    drawOnField(field) {
        return super.drawOnField(field, ITetramino.mapOfStates, ITetramino.color)
    }

    clearOnField(field, clearElement) {
        super.clearOnField(field, ITetramino.mapOfStates, clearElement)
    }

    moveDown(field) {
        return super.moveDown(field, ITetramino.mapOfStates, ITetramino.color);
    }

    moveRight(field) {
        return super.moveRight(field, ITetramino.mapOfStates, ITetramino.color);
    }

    moveLeft(field) {
        return super.moveLeft(field, ITetramino.mapOfStates, ITetramino.color);
    }

    rotateOnField(field) {
        return super.rotateOnField(field, ITetramino.mapOfStates, ITetramino.color);
    }
}

class STetramino extends Tetramino {
    static color = "#2dce1b"
    static mapOfStates = new Map(Object.entries({
        0: ["....",
            "..**",
            ".**.",
            "...."],
        1: ["..*.",
            "..**",
            "...*",
            "...."]
    }))

    constructor(xRotatePoint, yRotatePoint) {
        super(0, xRotatePoint, yRotatePoint);
    }

    drawOnField(field) {
        return super.drawOnField(field, STetramino.mapOfStates, STetramino.color)
    }

    clearOnField(field, clearElement) {
        super.clearOnField(field, STetramino.mapOfStates, clearElement)
    }

    moveDown(field) {
        return super.moveDown(field, STetramino.mapOfStates, STetramino.color);
    }

    moveRight(field) {
        return super.moveRight(field, STetramino.mapOfStates, STetramino.color);
    }

    moveLeft(field) {
        return super.moveLeft(field, STetramino.mapOfStates, STetramino.color);
    }

    rotateOnField(field) {
        return super.rotateOnField(field, STetramino.mapOfStates, STetramino.color);
    }
}

class ZTetramino extends Tetramino {
    static color = "#e06d0f"
    static mapOfStates = new Map(Object.entries({
        0: ["....",
            ".**.",
            "..**",
            "...."],
        1: ["...*",
            "..**",
            "..*.",
            "...."]
    }))

    constructor(xRotatePoint, yRotatePoint) {
        super(0, xRotatePoint, yRotatePoint);
    }

    drawOnField(field) {
        return super.drawOnField(field, ZTetramino.mapOfStates, ZTetramino.color)
    }

    clearOnField(field, clearElement) {
        super.clearOnField(field, ZTetramino.mapOfStates, clearElement)
    }

    moveDown(field) {
        return super.moveDown(field, ZTetramino.mapOfStates, ZTetramino.color);
    }

    moveRight(field) {
        return super.moveRight(field, ZTetramino.mapOfStates, ZTetramino.color);
    }

    moveLeft(field) {
        return super.moveLeft(field, ZTetramino.mapOfStates, ZTetramino.color);
    }

    rotateOnField(field) {
        return super.rotateOnField(field, ZTetramino.mapOfStates, ZTetramino.color);
    }
}

class LTetramino extends Tetramino {
    static color = "#ffc300"
    static mapOfStates = new Map(Object.entries({
        0: ["....",
            ".***",
            ".*..",
            "...."],
        1: ["..*.",
            "..*.",
            "..**",
            "...."],
        2: ["...*",
            ".***",
            "....",
            "...."],
        3: [".**.",
            "..*.",
            "..*.",
            "...."]
    }))

    constructor(xRotatePoint, yRotatePoint) {
        super(0, xRotatePoint, yRotatePoint);
    }

    drawOnField(field) {
        return super.drawOnField(field, LTetramino.mapOfStates, LTetramino.color)
    }

    clearOnField(field, clearElement) {
        super.clearOnField(field, LTetramino.mapOfStates, clearElement)
    }

    moveDown(field) {
        return super.moveDown(field, LTetramino.mapOfStates, LTetramino.color);
    }

    moveRight(field) {
        return super.moveRight(field, LTetramino.mapOfStates, LTetramino.color);
    }

    moveLeft(field) {
        return super.moveLeft(field, LTetramino.mapOfStates, LTetramino.color);
    }

    rotateOnField(field) {
        return super.rotateOnField(field, LTetramino.mapOfStates, LTetramino.color);
    }
}

class JTetramino extends Tetramino {
    static color = "#000bb4"
    static mapOfStates = new Map(Object.entries({
        0: ["....",
            ".***",
            "...*",
            "...."],
        1: ["..**",
            "..*.",
            "..*.",
            "...."],
        2: [".*..",
            ".***",
            "....",
            "...."],
        3: ["..*.",
            "..*.",
            ".**.",
            "...."]
    }))

    constructor(xRotatePoint, yRotatePoint) {
        super(0, xRotatePoint, yRotatePoint);
    }

    drawOnField(field) {
        return super.drawOnField(field, JTetramino.mapOfStates, JTetramino.color)
    }

    clearOnField(field, clearElement) {
        super.clearOnField(field, JTetramino.mapOfStates, clearElement)
    }

    moveDown(field) {
        return super.moveDown(field, JTetramino.mapOfStates, JTetramino.color);
    }

    moveRight(field) {
        return super.moveRight(field, JTetramino.mapOfStates, JTetramino.color);
    }

    moveLeft(field) {
        return super.moveLeft(field, JTetramino.mapOfStates, JTetramino.color);
    }

    rotateOnField(field) {
        return super.rotateOnField(field, JTetramino.mapOfStates, JTetramino.color);
    }
}

class TTetramino extends Tetramino {
    static color = "#900bec"
    static mapOfStates = new Map(Object.entries({
        0: ["....",
            ".***",
            "..*.",
            "...."],
        1: ["..*.",
            "..**",
            "..*.",
            "...."],
        2: ["..*.",
            ".***",
            "....",
            "...."],
        3: ["..*.",
            ".**.",
            "..*.",
            "...."]
    }))

    constructor(xRotatePoint, yRotatePoint) {
        super(0, xRotatePoint, yRotatePoint);
    }

    drawOnField(field) {
        return super.drawOnField(field, TTetramino.mapOfStates, TTetramino.color)
    }

    clearOnField(field, clearElement) {
        super.clearOnField(field, TTetramino.mapOfStates, clearElement)
    }

    moveDown(field) {
        return super.moveDown(field, TTetramino.mapOfStates, TTetramino.color);
    }

    moveRight(field) {
        return super.moveRight(field, TTetramino.mapOfStates, TTetramino.color);
    }

    moveLeft(field) {
        return super.moveLeft(field, TTetramino.mapOfStates, TTetramino.color);
    }

    rotateOnField(field) {
        return super.rotateOnField(field, TTetramino.mapOfStates, TTetramino.color);
    }
}
