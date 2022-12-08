class Placeable {
    constructor(xPos, yPos) {
        this.xPos = xPos
        this.yPos = yPos
    }
}

class HealObject extends Placeable {

    constructor(xPos, yPos, healEffect = 25) {
        super(xPos, yPos);
        this.healEffect = healEffect
    }

}
