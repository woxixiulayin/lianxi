#!/usr/bin/env python
import time

class Subject():

    def __init__(self):
        self.observer_list = []

    def register_observer(self, observer):
        self.observer_list.append(observer)

    def remove_observers(self, observer):
        self.observer_list.remove(observer)

    def notify_observer(self):
        pass


class Object():

    def update():
        pass


class Display():

    def display(self):
        print 'display weather'


class Weatherdata(Subject):

    def __init__(self):
        self.observer_list = []
        self.temperature = 0
        self.humidity = 0
        self.pressure = 0

    def change_action(self):
        for o in self.observer_list:
            o.update(self.temperature, self.humidity, self.pressure)

    def set_measurements(self, temperature, humidity, pressure):
        self.temperature = temperature
        self.humidity = humidity
        self.pressure = pressure

        self.change_action()


class current_condition_dis(Object, Display):

    def __init__(self, subject):
        subject.register_observer(self)
        self.temperature = 0
        self.humidity = 0
        self.pressure = 0

    def update(self, temperature, humidity, pressure):
        self.temperature = temperature
        self.humidity = humidity
        self.display(temperature, humidity)

    def display(self, temperature, humidity):

        print 'current temperature is %d and humidity is %d' % (temperature, humidity)


class forcast_dis(Object, Display):

    def __init__(self, subject):
        subject.register_observer(self)
        self.temperature = 0
        self.pre_temperature = 0
        self.pre_humidity = 0
        self.humidity = 0

    def update(self, temperature, humidity, pressure):
        self.temperature = (temperature + self.pre_temperature) / 2
        self.pre_temperature = temperature
        self.humidity = (humidity + self.pre_humidity) / 2
        self.pre_humidity = humidity
        self.display(self.temperature, self.humidity)

    def display(self, temperature, humidity):
        print 'forcast temperature is %d and humidity is %d' % (temperature, humidity)

if __name__ == '__main__':
    weather = Weatherdata()
    current = current_condition_dis(weather)
    forcast = forcast_dis(weather)
    weather.set_measurements(100, 95, 1000)
    time.sleep(1)
    weather.set_measurements(85, 105, 1000)
