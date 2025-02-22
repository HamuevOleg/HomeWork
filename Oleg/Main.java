class Technique {
    int year_of_creation;
    String name_of_tech;
    double max_speed;
    double mass_of_tech;
    int number_of_wheels;

    Technique(int year_of_creation, String name_of_tech) {
        this.year_of_creation = year_of_creation;
        this.name_of_tech = name_of_tech;
    }

    Technique(double max_speed, double mass_of_tech) {
        this(1999, "Nissan GTR");
        this.max_speed = max_speed;
        this.mass_of_tech = mass_of_tech;
    }

    Technique(int year_of_creation, String name_of_tech, double max_speed, int number_of_wheels, double mass_of_tech) {
        this.year_of_creation = year_of_creation;
        this.name_of_tech = name_of_tech;
        this.max_speed = max_speed;
        this.number_of_wheels = number_of_wheels;
        this.mass_of_tech = mass_of_tech;
    }

    /* if s_o_w > 0 => the object moves in the direction of the wind (V_total = V_tech + V_wind) =>
       if s_o_w > 0 => the object moves against of the wind (V_total = V_tech - V_wind) =>
       if s_o_w = 0 => wind doesn't exist (V_total = V_tech)
     */
    void average_speed_on_a_straight(double S, double t, double speed_of_wind) {
        double velocity_of_technique = 3.6 * (S / t);
        double total_velocity = speed_of_wind == 0 ? velocity_of_technique :
                velocity_of_technique + speed_of_wind;

        System.out.println( name_of_tech + " average speed on the straight of " + S + " meters is " + total_velocity + "km/h");
    }

    void calculate_max_load(int num_of_axles, double load_per_axle) {
        int numOfAxles = Math.abs(num_of_axles);
        double max_load = numOfAxles > 0 & numOfAxles> 1 ? mass_of_tech + (numOfAxles * load_per_axle) : 0;
        if (max_load > 0)
            System.out.println(name_of_tech + " maximum load is " + max_load);
        else
            System.out.println("Please fix your axles");
    }
}

class Auto extends Technique{
    String type_of_auto;
    Auto(double max_speed, double mass_of_tech, String type_of_auto) {
        super(max_speed, mass_of_tech);
        this.type_of_auto = type_of_auto;
    }
    Auto(int year_of_creation, String name_of_tech, double max_speed, int number_of_wheels, double mass_of_tech) {
        super(year_of_creation, name_of_tech, max_speed, number_of_wheels, mass_of_tech);
    }

    //V_adj = V_max(1 - ΔV_turn)^N_turns, where 1 is like 100% of max_velocity
    void nurburgring_race_time(boolean driver_is_racer, double turn_deceleration) {
        double trackLength = 20080.0;
        int numberOfTurns = 154;

        if (max_speed <= 0) {
            System.out.println("Error: Invalid maximum speed.");
            return;
        }

        double speedAdjustedForTurns = max_speed * Math.pow(1 - turn_deceleration, numberOfTurns);
        speedAdjustedForTurns = Math.max(speedAdjustedForTurns, 10);

        double timeOnTrack = trackLength / speedAdjustedForTurns / 60;
        double baseDelayFactor = 1 + (0.1 * numberOfTurns / 100); // General delay factor

        if (type_of_auto.equals("Sport")) {
            if (driver_is_racer) {
                System.out.printf("[Sport] %s completed the Nürburgring in %.2f minutes.%n", name_of_tech, timeOnTrack);
            } else {
                double timeWithDelay = timeOnTrack * baseDelayFactor;
                System.out.printf("[Sport] %s completed the Nürburgring in %.2f minutes (slower due to non-professional driving skills).%n",
                        name_of_tech, timeWithDelay);
            }
        } else {
            double additionalDelay = driver_is_racer ? 1.1 : 1.2; // Small delay for pros, larger for non-pros
            double totalTime = timeOnTrack * baseDelayFactor * additionalDelay;

            if (driver_is_racer) {
                System.out.printf("[%s] %s completed the Nürburgring in %.2f minutes (slower due to a non-sport vehicle).%n",
                        type_of_auto, name_of_tech, totalTime);
            } else {
                System.out.printf("[%s] %s completed the Nürburgring in %.2f minutes (much slower due to a non-sport vehicle and non-professional driving skills).%n",
                        type_of_auto, name_of_tech, totalTime);
            }
        }
    }

    void quality_check() {
        if (number_of_wheels == 0) {
            System.out.println(name_of_tech + " Quality check failed! This vehicle has no wheels.");
        } else if (number_of_wheels % 2 == 0) {
            System.out.println(name_of_tech + " Quality check passed successfully.");
        } else {
            System.out.printf("%s Quality check failed! The number of wheels (%d) must be even.%n",
                    name_of_tech, number_of_wheels);
        }
    }

    void fuel_consumption(double distance, double fuel_efficiency, boolean is_city, String road_type, double avg_speed) {
        double base_fuel_needed = (distance / 100) * fuel_efficiency;

        if (is_city) {
            base_fuel_needed *= 1.2;
        }

        if (mass_of_tech > 0) {
            base_fuel_needed *= (1 + mass_of_tech / 1000 * 0.05);
        }

        switch (road_type.toLowerCase()) {
            case "highway":
                base_fuel_needed *= 0.8;
                break;
            case "off-road":
                base_fuel_needed *= 1.3;
                break;
            case "regular":
                base_fuel_needed *= 1;
                break;
        }
        if (avg_speed > 120) {
            base_fuel_needed *= 1.15;
        } else if (avg_speed < 50) {
            base_fuel_needed *= 1.1;
        }

        System.out.printf("%s will consume approximately %.2f liters of fuel for %.1f km under current conditions.%n",
                name_of_tech, base_fuel_needed, distance);
    }
}

public class Main {
    public static void main(String[] args) {
    Technique tech1 = new Technique(2005, "Toyota Supra");
        tech1.average_speed_on_a_straight(1000, 30, 5);
        tech1.calculate_max_load(2, 500);


    Auto auto1 = new Auto(320.0, 1500.0, "Sport");
        auto1.type_of_auto = "Sport";
        auto1.average_speed_on_a_straight(2000, 60, 10);
        auto1.calculate_max_load(4, 600);
        auto1.quality_check();
        auto1.fuel_consumption(5000,10,false,"regular",80);
        auto1.nurburgring_race_time(true,0);

    Auto auto2 = new Auto(2018, "BMW M4", 280.0, 4, 1400.0);
        auto2.type_of_auto = "sport";
        auto2.nurburgring_race_time(true, 0.05);
        auto2.quality_check();

    Technique tech2 = new Auto(250.0, 1600.0, "SUV");
        tech2.average_speed_on_a_straight(1500, 50, 7);
        tech2.calculate_max_load(3, 550);
}
}