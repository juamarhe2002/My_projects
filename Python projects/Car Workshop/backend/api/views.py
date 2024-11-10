from django.shortcuts import render
from django.contrib.auth.models import User
from rest_framework import generics, mixins
from .serializer import EmployeeSerializer, UserSerializer, EstimateSerializer, TicketSerializer, TimeSlotSerializer, PartSerializer
from rest_framework.permissions import IsAuthenticated, AllowAny, IsAdminUser
from .models import Employee, Ticket, TimeSlot, Estimate, Part
from .permissions import IsAuthenticatedOrAdmin
from django.db.models import Q
from rest_framework.response import Response


class EmployeeList(generics.ListAPIView):
    serializer_class = UserSerializer
    permission_classes = [IsAuthenticated]

    def get_queryset(self):
        employee_list = User.objects.all().exclude(is_superuser=True)
        return employee_list

class EmployeeDelete(generics.DestroyAPIView):
    serializer_class = UserSerializer
    permission_classes = [IsAdminUser]

    def get_queryset(self):
        employee_list = User.objects.all().exclude(is_superuser=True)
        return employee_list
    
class EmployeeCreate(generics.CreateAPIView):
    queryset = User.objects.all()
    serializer_class = UserSerializer
    permission_classes = [IsAdminUser]

class EmployeeSigned(generics.GenericAPIView):
    serializer_class = UserSerializer
    permission_classes = [IsAuthenticated]

    def get(self, request):
        employee = self.request.user
        return Response(employee.username)
        

class TicketList(generics.ListAPIView):
    serializer_class = TicketSerializer
    permission_classes = [IsAuthenticated]

    def get_queryset(self):
        user = self.request.user

        if user.username == "admin_1":
            ticket_list = Ticket.objects.all()
        else:
            ticket_list = Ticket.objects.filter(Q(EmployeeAssigned = "None") | Q(EmployeeAssigned = user.username))

        return ticket_list
    
class TicketCreate(generics.CreateAPIView):
    queryset = Ticket.objects.all()
    serializer_class = TicketSerializer
    permission_classes = [IsAuthenticated]

class TicketUpdate(generics.UpdateAPIView):
    queryset = Ticket.objects.all()
    serializer_class = TicketSerializer
    permission_classes = [IsAuthenticated]

    def get(self, request, pk):
        ticket = Ticket.objects.get(id = pk)
        return Response(ticket.toJSON())

class TicketView(generics.GenericAPIView):
    serializer_class = TicketSerializer
    permission_classes = [IsAuthenticated]

    def get(self, request, pk):
        ticket = Ticket.objects.get(id = pk)
        return Response(ticket)

class TicketDelete(generics.DestroyAPIView):
    serializer_class = TicketSerializer
    permission_classes = [IsAuthenticated]

    def get_queryset(self):
        user = self.request.user

        if user.username == "admin_1":
            ticket_list = Ticket.objects.all()
        else:
            ticket_list = Ticket.objects.filter(Q(EmployeeAssigned = "None") | Q(EmployeeAssigned = user.username))

        return ticket_list
    
class EstimateUpdate(generics.UpdateAPIView):
    queryset = Estimate.objects.all()
    serializer_class = EstimateSerializer
    permission_classes = [IsAuthenticated]

class PartList(generics.ListAPIView):
    serializer_class = PartSerializer
    permission_classes = [IsAuthenticated]

    def get_queryset(self):
        ticket = self.request.path
        print(ticket)

        part_list = Part.objects.all()
        return part_list
    
class PartCreate(generics.CreateAPIView):
    queryset = Part.objects.all()
    serializer_class = PartSerializer
    permission_classes = [IsAuthenticated]

class PartDelete(generics.DestroyAPIView):
    queryset = Part.objects.all()
    serializer_class = PartSerializer
    permission_classes = [IsAuthenticated]

class PartUpdate(generics.UpdateAPIView):
    queryset = Part.objects.all()
    serializer_class = PartSerializer
    permission_classes = [IsAuthenticated]
