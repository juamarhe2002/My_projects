from django.contrib.auth.models import User
from rest_framework import serializers
from .models import Employee, Ticket, TimeSlot, Estimate, Part

class EmployeeSerializer(serializers.ModelSerializer):
    class Meta:
        model = Employee
        fields = ["PricePerHour"]

class UserSerializer(serializers.ModelSerializer):
    Employee = EmployeeSerializer()

    class Meta:
        model = User
        fields = ["id", "username", "password", "Employee"]
        #extra_kwargs = {"password": {"write_only:True"}}

    def create(self, validated_data):
        employee_data = validated_data.pop('Employee')
        user = User.objects.create_user(**validated_data)
        user.Employee = Employee.objects.create(user = user, **employee_data)
        user.save()
        return user
    
class EstimateSerializer(serializers.ModelSerializer):
    class Meta:
        model = Estimate
        fields = ["Description", "ExpectedCost", "Accepted"]

class TicketSerializer(serializers.ModelSerializer):
    Estimate = EstimateSerializer()
    class Meta:
        model = Ticket
        fields = ["id", "Brand", "Model", "RegistrationId", "Problem", "EmployeeAssigned", "Status", "TotalPrice", "Estimate"]
    
    def create(self, validated_data):
        estimate_data = validated_data.pop("Estimate")
        ticket = Ticket.objects.create(**validated_data)
        ticket.Estimate = Estimate.objects.create(Ticket=ticket,**estimate_data)
        ticket.save()

        return ticket
    
    def update(self, instance, validated_data):
        return super().update(instance, validated_data)

class PartSerializer(serializers.ModelSerializer):
    class Meta:
        model = Part
        fields = ["TicketId", "Name", "Amount", "UnitPrice", "TotalPrice"]
        extra_kwargs = {"TicketId": {"read_only":True}}

class TimeSlotSerializer(serializers.ModelField):
    class Meta:
        model = TimeSlot
        fields = ["Ticket", "StartTime", "EndTime"]
        extra_kwargs = {"Ticket": {"read_only":True}}