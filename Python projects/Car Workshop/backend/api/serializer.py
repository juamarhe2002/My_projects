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

    # def update(self, instance, validated_data):
    #     instance.Ticket = validated_data('Ticket', instance.Ticket)
    #     instance.Description = validated_data('Description', instance.Description)
    #     instance.ExpectedCost = validated_data('ExpectedCost', instance.ExpectedCost)
    #     instance.Accepted = validated_data('Accepted', instance.Accepted)
    #     return instance

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
        instance.id = validated_data.get('id', instance.id)
        instance.Brand = validated_data.get('Brand', instance.Brand)
        instance.Model = validated_data.get('Model', instance.Model)
        instance.RegistrationId = validated_data.get('RegistrationId', instance.RegistrationId)
        instance.Problem = validated_data.get('Problem')
        instance.EmployeeAssigned = validated_data.get('EmployeeAssigned', instance.EmployeeAssigned)
        instance.Status = validated_data.get('Status', instance.Status)
        instance.TotalPrice = validated_data.get('TotalPrice', instance.TotalPrice)
        
        estimate_data = validated_data.pop('Estimate')
        estimate = instance.Estimate

        instance.save()

        estimate.Description = estimate_data.get('Description', estimate.Description)
        estimate.ExpectedCost = estimate_data.get('ExpectedCost', estimate.ExpectedCost)
        estimate.Accepted = estimate_data.get('Accepted', estimate.Accepted)
        estimate.save()

        # ticket = Ticket.objects.get(id= instance.id)
        # return super().update(instance, validated_data)
        return instance

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