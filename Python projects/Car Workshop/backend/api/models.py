from django.db import models
from django.contrib.auth.models import User

# Create your models here.

class Employee(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE, related_name="Employee")
    PricePerHour = models.DecimalField(max_digits=10, decimal_places=2)

    def __str__(self):
        return self.user.username
    
class Ticket(models.Model):
    Brand = models.CharField(max_length=100)
    Model = models.CharField(max_length=100)
    RegistrationId = models.CharField(max_length=100)
    Problem = models.TextField()
    EmployeeAssigned = models.CharField(max_length=100)
    Status = models.CharField(max_length=100)
    TotalPrice = models.DecimalField(max_digits=100, decimal_places=2)

    def __str__(self):
        return self.RegistrationId

class Estimate(models.Model):
    Ticket = models.OneToOneField(Ticket, on_delete=models.CASCADE, related_name="Estimate")
    Description = models.TextField()
    ExpectedCost = models.DecimalField(max_digits=100, decimal_places=2)
    Accepted = models.BooleanField(default=False)

    def __str__(self):
        return self.Ticket.RegistrationId
    

class TimeSlot(models.Model):
    Ticket = models.ForeignKey(Ticket, on_delete=models.CASCADE, related_name="TimeSlots")
    StartTime = models.DateTimeField(auto_now=True)
    EndTime = models.DateTimeField(auto_now=True)
    
class Part(models.Model):
    TicketId = models.ForeignKey(Ticket, on_delete=models.CASCADE, related_name="Parts")
    Name = models.CharField(max_length=100)
    Amount = models.PositiveIntegerField()
    UnitPrice = models.DecimalField(max_digits=100, decimal_places=2)
    TotalPrice = models.DecimalField(max_digits=100, decimal_places=2)

    @property
    def total_price(self):
        self.TotalPrice = self.UnitPrice * self.Amount

    def __str__(self):
        return self.Name
    