class Tetramino {
    // TODO добавить состояния, цвет, точку поворота; методы отрисовки и поворота добавить в наследниках
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
        if (this.checkDraw(field, mapOfState, Field.clearElemColor)) {
            let xStart = this.xRotatePoint - 2
            let yStart = this.yRotatePoint - 1
            for (let dx = 0; dx < mapOfState[this.state][0].length; dx++) {
                for (let dy = 0; dy < mapOfState[this.state].length; dy++) {
                    if (mapOfState[this.state][dy][dx] === '*') {
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

    checkDraw(field, mapOfState, clearElement = Field.clearElemColor) {
        let xStart = this.xRotatePoint - 2
        let yStart = this.yRotatePoint - 1
        for (let dx = 0; dx < mapOfState[this.state][0].length; dx++) {
            for (let dy = 0; dy < mapOfState[this.state].length; dy++) {
                if (mapOfState[this.state][dy][dx] === '*') {
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

    clearOnField(field, mapOfState, clearElement = Field.clearElemColor) {
        this.drawOnField(field, mapOfState, clearElement)
    }

    moveDown(field, mapOfState, color) {
        if (this.checkMoveDown(field, mapOfState)) {
            this.clearOnField(field, mapOfState)
            this.yRotatePoint++
            return this.drawOnField(field, mapOfState, color)
        }
        return false
    }
    checkMoveDown(field, mapOfState, clearElement = Field.clearElemColor) {
        let xStart = this.xRotatePoint - 2
        let yStart = this.yRotatePoint
        for (let dx = 0; dx < mapOfState[this.state][0].length; dx++) {
            for (let dy = 0; dy < mapOfState[this.state].length; dy++) {
                if (mapOfState[this.state][dy][dx] === '*') {
                    if (0 <= xStart + dx && xStart + dx < field[0].length &&
                        0 <= yStart + dy && yStart + dy < field.length) {
                        if(field[yStart + dy][xStart + dx] !== clearElement)
                            return false
                    }
                }
            }
        }
        return true
    }

    moveRight(field, mapOfState, color) { }
    moveLeft(field, mapOfState, color) { }
    checkMoveRight(field, mapOfState) { }
    checkMoveLeft(field, mapOfState) { }
    rotateOnField(field, mapOfState, color) { }
    checkRotate(field, mapOfState) { }
}


class OTetramino extends Tetramino {
    static color = "#eccf19"
    static mapOfStates = new Map({
        0: ["....", ".**.", ".**.", "...."],
    })

    constructor(xRotatePoint, yRotatePoint) {
        super(0, xRotatePoint, yRotatePoint);
    }

    drawOnField(field) {
        super.drawOnField(field, OTetramino.mapOfStates, OTetramino.color)
    }

    clearOnField(field, clearElement) {
        super.clearOnField(field, OTetramino.mapOfStates, clearElement)
    }

    moveDown(field) {
        return super.moveDown(field, OTetramino.mapOfStates, OTetramino.color);
    }
}

class ITetramino extends Tetramino {
    static color = "#1b77ce"
    static mapOfStates = new Map({
        0: ["....", "****", "....", "...."],
        1: ["..*.", "..*.", "..*.", "..*."]
    })
}
