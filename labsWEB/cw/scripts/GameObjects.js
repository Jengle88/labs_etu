export class Placeable {
    constructor(point) {
        this.point = point
    }
}

export class HealObject extends Placeable {

    constructor(point, healEffect = 25) {
        super(point);
        this.healEffect = healEffect
    }

}
