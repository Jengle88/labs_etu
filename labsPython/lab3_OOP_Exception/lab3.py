class HouseScheme:
    def __init__(self, cnt_rooms, square_room, comb_bath):
        if type(cnt_rooms) is not int or type(square_room) is not int or type(comb_bath) is not bool or \
                cnt_rooms < 0 or square_room < 0:
            raise ValueError("Invalid value")
        self.cntRooms = cnt_rooms
        self.squareRoom = square_room
        self.combBath = comb_bath


class CountryHouse(HouseScheme):
    def __init__(self, cnt_rooms, square_room, comb_bath, cnt_floors, square_land):
        super().__init__(cnt_rooms, square_room, comb_bath)
        if type(cnt_floors) is not int or type(square_land) is not int or cnt_floors < 0 or square_land < 0:
            raise ValueError("Invalid value")
        self.cntFloors = cnt_floors
        self.squareLand = square_land

    def __str__(self):
        return "Country House: Количество жилых комнат {}, Жилая площадь {}, " \
               "Совмещенный санузел {}, Количество этажей {}, " \
               "Площадь участка {}.".format(self.cntRooms, self.squareRoom, self.combBath, self.cntFloors,
                                            self.squareLand)

    def __eq__(self, other):
        return self.squareRoom == other.squareRoom and self.squareLand == other.squareLand and abs(
            self.cntFloors - other.cntFloors) <= 1


class Apartment(HouseScheme):
    def __init__(self, cnt_rooms, square_room, comb_bath, floor, windows_dir):
        super().__init__(cnt_rooms, square_room, comb_bath)
        if type(floor) is not int or type(windows_dir) is not str or floor < 1 or windows_dir not in "NSWE" \
                or floor > 15:
            raise ValueError("Invalid value")
        self.floor = floor
        self.windowsDir = windows_dir

    def __str__(self):
        return 'Apartment: Количество жилых комнат {}, Жилая площадь {}, ' \
               'Совмещенный санузел {}, Этаж {}, Окна выходят на {}.' \
            .format(self.cntRooms, self.squareRoom, self.combBath, self.floor, self.windowsDir)


class CountryHouseList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def append(self, p_object):
        if type(p_object) is not CountryHouse:
            raise TypeError("Invalid type {}".format(type(p_object)))
        super().append(p_object)

    def total_square(self):
        sum = 0
        for item in self:
            sum += item.squareRoom
        return sum


class ApartmentList(list):
    def __init__(self, name):
        super().__init__()
        self.name = name

    def extend(self, iterable):
        for item in iterable:
            if type(item) is Apartment:
                self.append(item)

    def floor_view(self, floors, directions):
        low, up = floors
        it = filter(lambda x: True if low <= x.floor <= up and x.windowsDir in directions else False, self)
        for item in it:
            print("{}: {}".format(item.windowsDir, item.floor))



