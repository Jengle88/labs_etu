class Placeable {
    constructor(point) {
        this.point = point
    }
}

class HealObject extends Placeable {

    constructor(point, healEffect = 25) {
        super(point);
        this.healEffect = healEffect
    }

}
